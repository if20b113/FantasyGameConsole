print('Hello World from lua script file!')

print('calling native function from lua ... ')
result = native_func(4)
print('result: ' .. result)

next_entity_id = 0
entities = { }

function entity_create(start_pos)
    local new_id = 'e' .. next_entity_id
    next_entity_id = next_entity_id + 1

    entities[new_id] = { pos = start_pos }
    return new_id
end

function entity_translate(entity, value)
    entity.pos = entity.pos + value
end

entity_create(1)
entity_create(5)

function scripting_example_update(delta)
    local speed = 5
    for entity_id, entity in pairs(entities) do
        entity_translate(entity, delta * speed)
    end
    
    local new_entity_id = entity_create(0)

    print('scripting_example_update called! also adding new entity ' .. new_entity_id)
end