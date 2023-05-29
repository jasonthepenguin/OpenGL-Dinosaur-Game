#pragma once

#include <string>
#include <glad/glad.h>
#include <memory>



		/******************************************************************************************************************************************
		 * @class   : Graphics  
		 * @brief   : An abstract graphics class designed to be inherited and have the functions overriden by child classes.
		 * 
		 * @author  : William Halling 32233703
		 * @date    : April 2023
		 * @version : 1.0
		 ******************************************************************************************************************************************/

class Graphics
{
	public:

	// passed a gameObject as parameter?

			/******************************************************************************************************************************************
			 * @brief : renderTriangleStrip() 
			 * @brief : Virtual function which is used to render a triangle strip() this function will be overriden in child class
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual bool renderTriangleStrip() = 0;


			/******************************************************************************************************************************************
			 * @brief : renderModel() 
			 * @brief : Virtual function which is used to render a model this function will be overriden in child class
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual bool renderModel() = 0;


			/******************************************************************************************************************************************
			 * @brief : setViewport() 
			 * @brief : Virtual function which is used to set the view port for the camera this function will be overriden in child class
			 * @param :  x 	    - int variable for assigning the x coordinate of the camera  
			 * @param :  y 	    - int variable for assigning the y coordinate of the camera
			 * @param :  width  - int variable for assigning the width  of the camera view coordinate of the camera
			 * @param :  height - int variable for assigning the height of the camera view coordinate of the camera
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void setViewport(int x, int y, int width, int height) = 0;



			/******************************************************************************************************************************************
			 * @brief : enableDepthTest() 
			 * @brief : Virtual function which is used to allow depth testing of objects within the terrain will be overriden in child class 
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void enableDepthTest() = 0;
		

			/******************************************************************************************************************************************
			 * @brief  : init() 
			 * @brief  : Virtual function which is used to initialize classes, will be overriden in child class 
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void init() = 0;


			/******************************************************************************************************************************************
			 * @brief  : clearBuffers() 
			 * @brief  : Virtual function which is used to clear the VAO, VBO and EBOs  will be overriden in child class 
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void clearBuffers() = 0;


			/******************************************************************************************************************************************
			 * @brief  : clearColor() 
			 * @brief  : Virtual function which is used to clear the colour form objects, and items rendered will be overriden in child class 
			 * @param  : float r 		- variable for assigning how much red   an object or entity has 
			 * @param  : flaot g   		- variable for assigning how much green an object or entity has 
			 * @param  : flaot b 		- variable for assigning how much blue  an object or entity has 
			 * @param  : float alpha	- variable for assigning alpha value
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void clearColor(float r, float g, float b, float alpha) = 0;


			/******************************************************************************************************************************************
			 * @brief  : createVBO() 
			 * @brief  : Virtual function which is used to create Vertex buffer objects
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void createVBO() = 0;


			/******************************************************************************************************************************************
			 * @brief  : createVAO() 
			 * @brief  : Virtual function which is used to create VertexArrayObjects
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void createVAO() = 0;


			/******************************************************************************************************************************************
			 * @brief  : createEBO() 
			 * @brief  : Virtual function which is used to create Entity Buffer object
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void createEBO() = 0;


			/******************************************************************************************************************************************
			 * @brief  : bindVertexArray() 
			 * @brief  : Virtual function which is used to bind an arry of vertexs
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void bindVertexArray() = 0;


			/******************************************************************************************************************************************
			 * @brief  : bindVertexArray() 
			 * @brief  : Virtual function which is used to bind an arry of vertexs
			 * @param  : takes the amount of VAOS ??
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void bindVertexArray(int vao) = 0;
		

		
			/******************************************************************************************************************************************
			 * @brief  : unbindVertexArray() 
			 * @brief  : Virtual function which is used to unbind an arry of vertexs
			 * 
			 * @return : void
			 ******************************************************************************************************************************************/

		virtual void unbindVertexArray() = 0;
};

	
	/******************************************************************************************************************************************
	 * @class   : OpenGL() 
	 * @brief   : Extends on the base Graphics class, should really move into its own class but ran out of time
	 * 
	 * @author  : Jason
	 * @date    : April 2023
	 * @version : 1.0
	 ******************************************************************************************************************************************/


class OpenGL : public Graphics
{

	// passed a gameObject as parameter?

	
		/******************************************************************************************************************************************
		 * @brief  : renderTriangleStrip() 
		 * @brief  : function used to draw a triangle strip
		 * 
		 * @return : bool returns true
		 ******************************************************************************************************************************************/

	bool renderTriangleStrip()
	{
		return true;
	}


		/******************************************************************************************************************************************
		 * @brief  : renderModel() 
		 * @brief  : function used to render a game Model
		 * 
		 * @return : bool returns true
		 ******************************************************************************************************************************************/

	bool renderModel()
	{
		return true;
	}


		/******************************************************************************************************************************************
		 * @brief : setViewport() 
		 * @brief : function is used to set the view port for the camera this function will be overriden in child class
		 * @param :  x 	    - int variable for assigning the x coordinate of the camera  
		 * @param :  y 	    - int variable for assigning the y coordinate of the camera
		 * @param :  width  - int variable for assigning the width  of the camera view coordinate of the camera
		 * @param :  height - int variable for assigning the height of the camera view coordinate of the camera
		 * @return : void
		 ******************************************************************************************************************************************/

	void setViewport(int x, int y, int width, int height)
	{
		//glViewport(0, 0, width, height);
		glViewport(x, y, width, height);
	}


		/******************************************************************************************************************************************
		 * @brief : enableDepthTest() 
		 * @brief : function is used to allow depth testing of objects within the terrain will be overriden in child class 
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void enableDepthTest() 
	{
		glEnable(GL_DEPTH_TEST);
	}


		/******************************************************************************************************************************************
		 * @brief  : init() 
		 * @brief  : function is used to initialize classes, will be overriden in child class 
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void init() 
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		 {
			std::cout << "Failed to initialize GLAD" << std::endl;

			exit(0);
		}
	}


		/******************************************************************************************************************************************
		 * @brief  : clearBuffers() 
		 * @brief  : function is used to clear the VAO, VBO and EBOs 
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void clearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


		/******************************************************************************************************************************************
		 * @brief  : clearColor() 
		 * @brief  : function is used to clear the colour form objects, and items rendered will be overriden in child class 
		 * @param  : float r 		- variable for assigning how much red   an object or entity has 
		 * @param  : flaot g   		- variable for assigning how much green an object or entity has 
		 * @param  : flaot b 		- variable for assigning how much blue  an object or entity has 
		 * @param  : float alpha	- variable for assigning alpha value
		 * @return : void
		 ******************************************************************************************************************************************/

	void clearColor(float r, float g, float b, float alpha)
	{
		//glClearColor(0.52f, 0.80f, 0.9f, 1.0f);
		glClearColor(r, g, b, alpha);
	}


		/******************************************************************************************************************************************
		 * @brief  : bindVertexArray() 
		 * @brief  : function is used to bind an array of vertexs
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void bindVertexArray(int vao)
	{
		glBindVertexArray(vao);
	}


		/******************************************************************************************************************************************
		 * @brief  : unbindVertexArray() 
		 * @brief  : function is used to unbind an array of vertexs
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void unbindVertexArray()
	{
		glBindVertexArray(0);
	}


		/******************************************************************************************************************************************
		 * @brief  : createVBO() 
		 * @brief  : Virtual function which is used to unbind an array of vertexs
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void createVBO()
	{

	}
		/******************************************************************************************************************************************
		 * @brief  : createVAO() 
		 * @brief  : Virtual function which is used to unbind an array of vertexs
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void createVAO()
	{

	}

		/******************************************************************************************************************************************
		 * @brief  : createEBO() 
		 * @brief  : function which is used to create EBOS
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void createEBO()
	{

	}


		/******************************************************************************************************************************************
		 * @brief  : bindVertexArray() 
		 * @brief  : function which is used to bind EBOS
		 * 
		 * @return : void
		 ******************************************************************************************************************************************/

	void bindVertexArray()
	{

	}
};


		/******************************************************************************************************************************************
		 * @class   : Graphics_Factory() 
		 * @brief   : Factory Pattern class for the Graphics Factory pattern
		 * 
		 * @date    : April 2023
		 * @author  : William Halling
		 * @version : 1.0
		 ******************************************************************************************************************************************/

class Graphics_Factory
{
public:

		/******************************************************************************************************************************************
		 * @brief   : Create() 
		 * @brief   : Used to create the API
		 * @param	: type std::string - the type of Graphics API
		 ******************************************************************************************************************************************/

	std::unique_ptr <Graphics> Create(std::string type)
	{
		if (type == "opengl")
		{
			return std::make_unique<OpenGL>();
		}
	}
};