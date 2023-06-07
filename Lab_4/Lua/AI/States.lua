
state_idle = {}
state_idle["Enter"] = function(npc)
    npc:playAnimation("idle")
  
end
state_idle["Execute"] = function(npc)

   npc:ForwardLook()
    --npc:lookAtplayer()
   cooldown = npc:getCooldown()

   if(npc:distanceToPlayer() <= 10) then
        npc.npcFSM:changeState("state_chase")
   elseif(cooldown == false) then
      npc.npcFSM:changeState("state_wander")
   end
   

   
end
state_idle["Exit"] = function(npc)

end

state_idle["onMessage"] = function(npc,msg)

   
    if(msg.msg==1) then
        print("I'm coming to help! from idle")
        local position = msg.extraInfo
       -- print("Received position: ", position.x, position.y, position.z)
        npc:setWaypoint(position)
        npc.npcFSM:changeState("state_gotoWaypoint")
      end
 
end


-----------------------------------------
-- tables that C++ can access to keep track and change state, pass the NPC to this lua state, lua then calls the appropriate npc functions
state_chase = {}
state_chase["Enter"] = function(npc)
        --print("Entering state_chase")
        npc:playAnimation("run")
        ourID = npc:getID()
      receiverID = npc:findClosestNPC()
      print(receiverID)
      print("Someone come over here!")
        npc:sendMessage(0.0 ,ourID, receiverID,1, npc.position)
end
state_chase["Execute"] = function(npc)
        npc:lookAtplayer()
       -- print('hi')
        if(npc:distanceToPlayer() <= 5 - 0.5) then
            npc.npcFSM:changeState("state_attack")
        elseif(npc:distanceToPlayer() > 10 + 0.5) then
            npc.npcFSM:changeState("state_idle")
        else    
            npc:moveToPlayer()
        end

end
state_chase["Exit"] = function(npc)
        --nothing for now
end

state_chase["onMessage"] = function(npc,msg)



end

-----------------------------------------

state_attack = {}
state_attack["Enter"] = function(npc)
     
     npc:playAnimation("attack")
end
state_attack["Execute"] = function(npc)

    npc:lookAtplayer()

    if(npc:distanceToPlayer() >= 5 + 0.5) then
            npc.npcFSM:changeState("state_chase")
    else
        --npc:lookAtplayer()
    end

end
state_attack["Exit"] = function(npc)
    --nothing for now
end

state_attack["onMessage"] = function(npc,msg)



end


----------------------------------------
state_wander = {}
state_wander["Enter"] = function(npc)
    npc:playAnimation("run")
    npc:chooseRandomDirection()
end

state_wander["Execute"] = function(npc)

    cooldown = npc:getCooldown()

    if(cooldown == true ) then
        npc.npcFSM:changeState("state_idle")
    elseif(npc:distanceToPlayer() <= 10) then
        npc.npcFSM:changeState("state_chase")
    
    else
        npc:wander()
    end

end

state_wander["Exit"] = function(npc)

end

state_wander["onMessage"] = function(npc,msg)

    
    if(msg.msg==1) then
        print("I'm coming to help! From wander")
        local position = msg.extraInfo
        -- print("Received position: ", position.x, position.y, position.z)
         npc:setWaypoint(position)
         npc.npcFSM:changeState("state_gotoWaypoint")


      end

end


----------------------------

state_gotoWaypoint = {}
state_gotoWaypoint["Enter"] = function(npc)
    
    npc:playAnimation("run")
end

state_gotoWaypoint["Execute"] = function(npc)
    
    npc:lookAtplayer()

    if(npc:distanceToWaypoint() < 3) then
        npc.npcFSM:changeState("state_idle")

    else
        npc:moveToWaypoint()
    end


end

state_gotoWaypoint["Exit"] = function(npc)
    
end

state_gotoWaypoint["onMessage"] = function(npc, msg)

    
end
