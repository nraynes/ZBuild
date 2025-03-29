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

if test -d $HOME/ZBuild; then
    echo "Removing old install"
    rm -rf $HOME/ZBuild
fi

if test -d $project_path/zbuild-install; then
    echo "Installing ZBuild"
    mkdir $HOME/ZBuild
    cp zbuild-install/zbuild-0.1.0.tar.gz $HOME/ZBuild
    cd $HOME/ZBuild
    tar -xzf zbuild-0.1.0.tar.gz
    rm zbuild-0.1.0.tar.gz
    echo "Installed ZBuild to $HOME/ZBuild"
else
    echo "No ZBuild package to install"
fi