# Hollow Sun Save Editor

A simple command-line tool to edit and manage save files for the game **Hollow Sun**. This tool allows players to modify game attributes like health, stamina, location, money, and account money directly within the save file.

## Features

- Modify health and stamina values
- Update the location in the save file
- Edit money and account money values
- Simple text-based interface for easy usage
## Directory
Make sure you put the executable in the same directory as Hollow Sun, that way, your save file can be read
## Installation
Simply go to releases, go to the latest release, and download the relevant executable file.
## Installation from source

To get started, simply clone this repository to your local machine:

```bash
git clone https://github.com/PhotonMastr/HollowSunSaveEditor.git
```
Then, CD into the directory
```bash
cd HollowSunSaveEditor
```
Then, use the makefile to build
#### On linux 

```bash
make
```
#### On Windows
```bash
mingw32-make
```

## Notes
Edit your save at will, however it definitely loses some fun in the game.
Be careful with location editing, maybe look through the code to see where the location is bringing you.
