--
-- Created by IntelliJ IDEA.
-- User: korisd
-- Date: 7/26/18
-- Time: 11:47 AM
-- To change this template use File | Settings | File Templates.
--

--
require('types')

--trial 9 "Toggle Up to Down"
return {
    [1] = { x = 20.00, y = 3.25, z = 21.3, eeo = 0, velocity = 5, type = DISCRETE_W, precision = 1, shape = "linear", smoothness = 2, tolerance = 2 },
    [2] = { x = 23.2, y = 3.25, z = 21.3, eeo = 0, velocity = 5, type = DISCRETE_W, precision = 1, shape = "linear", smoothness = 2, tolerance = 2 },
    [3] = { velocity = 5, type = SERVO_R, s1 = 0, s2 = 0, s3 = 0, s4 = 210, s5 = 0, s6 = 0 },
    [4] = { velocity = 5, type = SERVO_R, s1 = 0, s2 = 0, s3 = 0, s4 = -210, s5 = 0, s6 = 0 },
    [5] = { x = 20.00, y = 3.25, z = 21.3, eeo = 0, velocity = 5, type = DISCRETE_W, precision = 1, shape = "linear", smoothness = 2, tolerance = 2 },
}

