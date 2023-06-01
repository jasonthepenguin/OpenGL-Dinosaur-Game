
state_idle = {}
state_idle["Enter"] = function(npc)
    --nothing for now
    print('ok')
    npc:playAnimation("idle")
   -- print('ok')
end
state_idle["Execute"] = function(npc)
    --nothing for now
   -- print('ok')
   npc:ForwardLook()
end
state_idle["Exit"] = function(npc)

end


-----------------------------------------

state_chase = {}
state_chase["Enter"] = function(npc)
        --nothing for now
        npc:playAnimation("run")
end
state_chase["Execute"] = function(npc)
        --nothing for now
end
state_chase["Exit"] = function(npc)
        --nothing for now
end

-----------------------------------------

state_attack = {}
state_attack["Enter"] = function(npc)
     --nothing for now
     npc:playAnimation("attack")
end
state_attack["Execute"] = function(npc)
    --nothing for now
end
state_attack["Exit"] = function(npc)
    --nothing for now
end
