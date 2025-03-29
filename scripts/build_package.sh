# Run using SUDO. Keep in the scripts directory in project.

project_path=""
real_path=$(realpath $0)
IFS='/' read -ra path_list <<< $real_path
for dir in $path_list
do
    project_path+="/$dir"
    if [ $dir == "ZBuild" ]; then
        break
    fi
done
version="0.1.0"
cd $project_path

# Build
echo "Building ZBuild"
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Remove old install
if test -d zbuild-install; then
    echo "Removing old installs"
    rm -rf zbuild-install
fi

# # Install
echo "Installing ZBuild"
cmake -B build -DCMAKE_INSTALL_PREFIX=./zbuild-install
cmake --build build
cmake --install build

# # Package
echo "Packaging ZBuild"
cd zbuild-install
tar -cvzf zbuild-$version.tar.gz *

echo "Done"
