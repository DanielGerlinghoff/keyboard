# Get the script name and the destination host and path
script_name=$(basename "$0")
destination="$USERNAME@$SERVER:$DIRECTORY"

# Define the list of files to exclude
exclude_list="deploy_credentials.sh,README.md"

# Convert the list to an array
IFS=',' read -r -a exclude_array <<< "$exclude_list"

# Parse the command line arguments
while getopts ":f:" opt; do
  case $opt in
    f) file_to_copy="$OPTARG";;
    \?) echo "Invalid option: -$OPTARG" >&2;;
  esac
done

# Construct the list of files to copy
files_to_copy=""
for file in *; do
  # Skip directories, the script itself, and files in the exclude list
  if [[ -f "$file" && "$file" != "$script_name" && ! " ${exclude_array[@]} " =~ " $file " ]]; then
    # Add the file to the list of files to copy
    if [[ -z $file_to_copy ]] || [[ "$file" == "$file_to_copy" ]]; then
      files_to_copy+=" $file"
    fi
  fi
done

# Copy the files to the destination using a single scp command
scp $files_to_copy "$destination"
