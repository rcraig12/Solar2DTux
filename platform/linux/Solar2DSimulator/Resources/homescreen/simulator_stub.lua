------------------------------------------------------------------------------
--
-- This file is part of the Corona game engine.
-- For overview and more information on licensing please refer to README.md 
-- Home page: https://github.com/coronalabs/corona
-- Contact: support@coronalabs.com
--
------------------------------------------------------------------------------

local simulator = {}
local json = require("json")

function simulator.analytics()
end
function simulator.getPreference()
end
function simulator.getRecentProjects()
	return {}
end
function simulator.getSubscription()
end
function simulator.setCursorRect()
end
function simulator.setProjectResourceDirectory()
end
function simulator.show(...)
	print("SIMULATOR SHOW: ", ...)
end
return simulator