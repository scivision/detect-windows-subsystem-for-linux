#!/usr/bin/env python3
"""
@functools.cache is optional; greatly speeds up subsequent calls
"""
import platform
import os
import shutil
import subprocess
import functools


@functools.cache
def is_wsl() -> bool:
    """
    detects if Python is running in WSL
    """
    return "microsoft-standard-WSL" in platform.uname().release


@functools.cache
def wsl_available() -> bool:
    """
    detect if Windows Subsystem for Linux is available from Windows
    """
    if os.name != "nt":
        return False
    if not shutil.which("wsl"):
        return False
    r = subprocess.run(["wsl", "uname", "-r"], text=True, capture_output=True)
    return r.returncode == 0 and "microsoft-standard-WSL" in r.stdout


if __name__ == "__main__":
    print("is_wsl: ", is_wsl())
    print("is WSL available: ", wsl_available())
