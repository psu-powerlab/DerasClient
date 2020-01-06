# DerasClient
General client for powerlab 2030.5 development

## Setup
### Linux Environment
``` console
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install git build-essential gcc
mkdir ~/Src ~/Dev ~/Dev/Logs
```
### Code Blocks
Download and install the latest binary release of code blocks from http://www.codeblocks.org/downloads.

### Boost Libraries
Download the current release of boost libraries from https://www.boost.org/users/download/. Then exctract to *~/Src* folder.

### Project
``` console
cd ~/Dev
git clone https://github.com/psu-powerlab/DerasClient
```

Open the *.cbp* file and navigate to the project search directories *Project->build options->Search directories. Add boost libraries to the project search directories.
