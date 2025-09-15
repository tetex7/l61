---
--- Created by tete.
--- DateTime: 05/07/2025 09:01 PM
---
--- @meta


l61 = {
    ---return a pwd
    ---@return string
    getPwd = function() end,

    ---@param freg string | integer
    pushEventBus = function(freg) end,
    fs = {
        ---@param path string
        ---@return boolean
        exists = function(path) end
    }
}


---@param lib string
---@return table
function mountLib(lib) end