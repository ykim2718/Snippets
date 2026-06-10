"""
y, 2024.6.10
importlib_metadata - check_package_paths.py
ChatGPT3.5
"""

import importlib_metadata


def check_package_paths():
    for dist in importlib_metadata.distributions():
        name = dist.metadata.get('Name', 'Unknown')
        version = dist.version
        location = dist.locate_file('')
        if location is None or location == '':
            print(f"Warning: Package '{name}' (version {version}) has no valid path.")
        else:
            print(f"Package: {name}, Version: {version}, Location: {location}")


if __name__ == "__main__":
    check_package_paths()
