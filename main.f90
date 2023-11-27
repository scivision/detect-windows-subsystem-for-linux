program main

use, intrinsic :: iso_c_binding, only : C_BOOL

implicit none

interface
logical(C_BOOL) function is_wsl() bind(C)
import C_BOOL
end function
end interface

print '(a,L1)', 'Fortran: is_WSL: ', is_wsl()

end program
