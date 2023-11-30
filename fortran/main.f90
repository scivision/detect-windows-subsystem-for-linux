program main

use, intrinsic :: iso_c_binding, only : C_INT

implicit none

interface
integer(C_INT) function is_wsl() bind(C)
import
end function
end interface

print '(a,i1)', 'WSL: ', is_wsl()

end program
