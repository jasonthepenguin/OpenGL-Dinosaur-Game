#pragma once





#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Following the guide from http://tfc.duke.free.fr/coding/md2-specs-en.html

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Texture.h"
#include "Shader.h"

#include <utility>
#include <cctype>

	class MD2_TEST
	{
	public:

		//--------------
		Shader* m_shaderProgram;
		glm::vec3 m_position;
		std::unique_ptr<OpenGLTexture> m_texture;


		int n = 0;            // current frame being played
		float interp = 0.0;
		std::vector<std::pair<int, int>> animationCycles; // vector of animation cycles, each pair contains starting frame and ending frame 
		int currAnimCycle = 0;

		std::vector<float> vertices;
		std::vector<int> VAOvector;
		std::vector<int> VBOvector;
		std::vector<int> verticesCount;

		glm::mat4 rotationMatrix4x4 = glm::mat4(1.0);

		/* Vector */
		typedef float vec3_t[3];

		/* MD2 header */
		struct md2_header_t
		{
			int ident;
			int version;

			int skinwidth;
			int skinheight;

			int framesize;

			int num_skins;
			int num_vertices;
			int num_st;
			int num_tris;
			int num_glcmds;
			int num_frames;

			int offset_skins;
			int offset_st;
			int offset_tris;
			int offset_frames;
			int offset_glcmds;
			int offset_end;
		};

		/* Texture name */
		struct md2_skin_t
		{
			char name[64];
		};

		/* Texture coords */
		struct md2_texCoord_t
		{
			short s;
			short t;
		};

		/* Triangle info */
		struct md2_triangle_t
		{
			unsigned short vertex[3];
			unsigned short st[3];
		};

		/* Compressed vertex */
		struct md2_vertex_t
		{
			unsigned char v[3];
			unsigned char normalIndex;
		};

		/* Model frame */
		struct md2_frame_t
		{
			vec3_t scale;
			vec3_t translate;
			char name[16];
			struct md2_vertex_t* verts;
		};

		/* GL command packet */
		struct md2_glcmd_t
		{
			float s;
			float t;
			int index;
		};

		/* MD2 model structure */
		struct md2_model_t
		{
			struct md2_header_t header;

			struct md2_skin_t* skins;
			struct md2_texCoord_t* texcoords;
			struct md2_triangle_t* triangles;
			struct md2_frame_t* frames;
			int* glcmds;

			GLuint tex_id;
		};




		/*** An MD2 model ***/
		struct md2_model_t md2file;

		void setUpAnimationCycles()
		{
			std::cout << "The offset_frames values is : " << md2file.header.offset_frames << std::endl;
			std::cout << "The number of frames is : " << md2file.header.num_frames << std::endl;
			std::string curr_anim_name;
			curr_anim_name = md2file.frames[0].name;
			std::string next_anim_name;
			int anim_start = 0;
			int anim_end = 0;

			for (int i = 0; i < md2file.header.num_frames ; i++)
			{
				next_anim_name = md2file.frames[i].name;
				
				if(extractName(curr_anim_name) != extractName(next_anim_name))
				{
					curr_anim_name = next_anim_name;  // means we are onto the next animation, store the name of the new current animation name


					anim_end = i - 1;   // frame representing the end of that animation is the current frame minus 1 
					animationCycles.push_back(std::make_pair(anim_start, anim_end));  // animation start and end are added as a pair to animation cycle vector

					anim_start = i; // since this is "i" now represents start of new animation cycle, store that in anim_start, which will be used to create the next pair once animation names mismatch again.

				}

			}
			// Add the last animation cycle to the animationCycles vector
			anim_end = md2file.header.num_frames - 1;
			animationCycles.push_back(std::make_pair(anim_start, anim_end));
		}

		std::string extractName(const std::string& input) {
			std::string result;
			for (const char& c : input) {
				if (std::isalpha(c)) {
					result += c;
				}
			}
			return result;
		}


		void playNextAnimation()
		{
			currAnimCycle++;
			if (currAnimCycle >= animationCycles.size()) {
				currAnimCycle = 0;
			}
		}

			int	ReadMD2Model( char* filename, char* textureFileName)
			{
			m_texture = std::make_unique<OpenGLTexture>(); // replacing with openGL texture
			std::string fName = textureFileName;
			m_texture->setFileName(fName);
				// flip test
			m_texture->flip = false;

			m_texture->load();
			md2_model_t* mdl = &md2file;


			FILE* fp;
			int i;

			fopen_s(&fp, filename, "rb");

			if (!fp)
			{
				fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
				return 0;
			}

			// Read header 
			fread(&mdl->header, 1, sizeof(struct md2_header_t), fp);

			if ((mdl->header.ident != 844121161) || (mdl->header.version != 8))
			{
				// Error! 
				fprintf(stderr, "Error: bad version or identifier\n");
				fclose(fp);
				return 0;
			}

			// Memory allocations 
			mdl->skins = (struct md2_skin_t*)
				malloc(sizeof(struct md2_skin_t) * mdl->header.num_skins);
			mdl->texcoords = (struct md2_texCoord_t*)
				malloc(sizeof(struct md2_texCoord_t) * mdl->header.num_st);
			mdl->triangles = (struct md2_triangle_t*)
				malloc(sizeof(struct md2_triangle_t) * mdl->header.num_tris);
			mdl->frames = (struct md2_frame_t*)
				malloc(sizeof(struct md2_frame_t) * mdl->header.num_frames);
			mdl->glcmds = (int*)malloc(sizeof(int) * mdl->header.num_glcmds);

			// Read model data 
			fseek(fp, mdl->header.offset_skins, SEEK_SET);
			fread(mdl->skins, sizeof(struct md2_skin_t),
				mdl->header.num_skins, fp);

			fseek(fp, mdl->header.offset_st, SEEK_SET);
			fread(mdl->texcoords, sizeof(struct md2_texCoord_t),
				mdl->header.num_st, fp);

			fseek(fp, mdl->header.offset_tris, SEEK_SET);
			fread(mdl->triangles, sizeof(struct md2_triangle_t),
				mdl->header.num_tris, fp);

			fseek(fp, mdl->header.offset_glcmds, SEEK_SET);
			fread(mdl->glcmds, sizeof(int), mdl->header.num_glcmds, fp);

			// Read frames 
			fseek(fp, mdl->header.offset_frames, SEEK_SET);
			for (i = 0; i < mdl->header.num_frames; ++i)
			{
				// Memory allocation for vertices of this frame 
				mdl->frames[i].verts = (struct md2_vertex_t*)
					malloc(sizeof(struct md2_vertex_t) * mdl->header.num_vertices);

				// Read frame data 
				fread(mdl->frames[i].scale, sizeof(vec3_t), 1, fp);
				fread(mdl->frames[i].translate, sizeof(vec3_t), 1, fp);
				fread(mdl->frames[i].name, sizeof(char), 16, fp);
				fread(mdl->frames[i].verts, sizeof(struct md2_vertex_t),mdl->header.num_vertices, fp);
			}

			fclose(fp);

				// Figure out when each animation starts and ends for this MD2
			setUpAnimationCycles();
			return 1;
		}
		

		/**
 * Render the model with interpolation between frame n and n+1.
 * interp is the interpolation percent. (from 0.0 to 1.0)
 */
		void loadData()
		{
			md2_model_t* mdl = &md2file;
			int i, j;
			GLfloat s, t;
			vec3_t v_curr, v_next, v, norm;
			float* n_curr, * n_next;
			struct md2_frame_t* pframe1, * pframe2;
			struct md2_vertex_t* pvert1, * pvert2;
			m_shaderProgram = new Shader("shaders/md2_vert.shader", "shaders/md2_frag.shader");
			m_position = glm::vec3(0.0f, 0.0f, 0.0f);

			// PLAN : need to iterate through each frame 

			//for (int n = 0; n < mdl->header.num_frames ; n++) {
			for (int n = 0; n < mdl->header.num_frames - 1; n++) {

				verticesCount.push_back(0);

				for (i = 0; i < mdl->header.num_tris; ++i)
				{
					/* Draw each vertex */
					for (j = 0; j < 3; ++j)
					{
						pframe1 = &mdl->frames[n];
						pframe2 = &mdl->frames[n + 1];
						pvert1 = &pframe1->verts[mdl->triangles[i].vertex[j]];
						pvert2 = &pframe2->verts[mdl->triangles[i].vertex[j]];

						/* Compute texture coordinates */
						s = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].s / mdl->header.skinwidth;
						t = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].t / mdl->header.skinheight;

						 /* Calculate vertex real position */
						v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
						v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
						v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

						v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
						v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
						v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

					
						// BIND VAO, VBO for this frame, add to our vectors
						vertices.push_back(v_curr[0]);		// vertices for the current frame position
						vertices.push_back(v_curr[1]);
						vertices.push_back(v_curr[2]);

						// vertices for the next frame position
						vertices.push_back(v_next[0]);
						vertices.push_back(v_next[1]);
						vertices.push_back(v_next[2]);

						// adding the texture coordinates
						vertices.push_back(s);
						vertices.push_back(t);

						verticesCount[n] = verticesCount[n] + 1; // for each vertex
					}
				}

				// NOW LOOPS BACK FOR NEXT FRAME
				unsigned int vbo, vao;
				// SETTING UP THE VAO AND VBO
				glGenBuffers(1, &vbo);
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

				// Current Frame Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
				glEnableVertexAttribArray(0);

				// Next  Frame Position attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

				// Texture Coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
				glEnableVertexAttribArray(2);

				VBOvector.push_back(vbo);
				VAOvector.push_back(vao);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				vertices.clear();
			}
		}


		//void Render(int frame, float interpolation, glm::mat4& view, glm::mat4& projection) {
		void Render(const glm::mat4& view, const glm::mat4& projection, glm::mat4 model = glm::mat4(1.0)) {


			int frame = n;
			float interpolation = interp;

			//assert(m_modelLoaded && m_textureLoaded && m_bufferInitialized);

			m_texture->bindTexture(0);

			
			model = glm::translate(model, m_position); //* glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
			model *= rotationMatrix4x4;
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			//model *= rotationMatrix4x4;
			model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));


			m_shaderProgram->use();

	
			m_shaderProgram->setMat4("view", view);
			m_shaderProgram->setMat4("projection", projection);
			m_shaderProgram->setMat4("model", model);
			m_shaderProgram->setMat4("modelView", view * model);
			glBindVertexArray(VAOvector[frame]);
			m_shaderProgram->setFloat("interpolation", interpolation);
			glDrawArrays(GL_TRIANGLES, 0, verticesCount[frame]);
			glBindVertexArray(0);
			m_texture->unbind();
		}


		void cleanup()
		{
			FreeModel(&md2file);
		}


		void FreeModel(struct md2_model_t* mdl)
		{
			int i;

			if (mdl->skins)
			{
				free(mdl->skins);
				mdl->skins = NULL;
			}

			if (mdl->texcoords)
			{
				free(mdl->texcoords);
				mdl->texcoords = NULL;
			}

			if (mdl->triangles)
			{
				free(mdl->triangles);
				mdl->triangles = NULL;
			}

			if (mdl->glcmds)
			{
				free(mdl->glcmds);
				mdl->glcmds = NULL;
			}

			if (mdl->frames)
			{
				for (i = 0; i < mdl->header.num_frames; ++i)
				{
					free(mdl->frames[i].verts);
					mdl->frames[i].verts = NULL;
				}

				free(mdl->frames);
				mdl->frames = NULL;
			}
		}

		MD2_TEST()
		{

		}

		void Animate(float deltaTime)
		{
			
			interp += 10 * deltaTime;

			int start = 0;
			int end = getEndFrame() - 1;


			// TEST ANIM CYCLES CODE
			start = animationCycles[currAnimCycle].first;
			end = animationCycles[currAnimCycle].second;
			//-----------------------------------------------

			if ((n < start) || (n > end))
				n = start;

			if (interp >= 1.0f)
			{
				// Move to next frame 
				interp = 0.0f;
				(n)++;

				if (n >= end)
					n = start;
			}
		}



		int getEndFrame()
		{
			return md2file.header.num_frames;
		}

		void setUpVertexData()
		{

		}
	};