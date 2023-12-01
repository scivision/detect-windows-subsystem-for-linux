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
def is_wsl() -> int:
    """
    detects if Python is running in WSL
    """

    r = platform.uname().release

    if r.endswith("-Microsoft"):
        return 1
    elif r.endswith("microsoft-standard-WSL"):
        return 2

    return 0


@functools.cache
def wsl_available() -> bool:
    """
    detect if Windows Subsystem for Linux is available from Windows
    """
    if os.name != "nt" or not shutil.which("wsl"):
        return False
    try:
        r = subprocess.check_output(["wsl", "uname", "-r"], text=True, timeout=15)
        return "microsoft-standard-WSL" in r.stdout
    except subprocess.SubprocessError:
        return False


if __name__ == "__main__":
    print("WSL: ", is_wsl())
    print("is WSL available: ", wsl_available())
