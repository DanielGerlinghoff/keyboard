# Get the script name and the destination host and path
script_name=$(basename "$0")
destination="$USERNAME@$SERVER:$DIRECTORY"

# Define the list of files to exclude
exclude_list="deploy_credentials.sh,README.md"

# Convert the list to an array
IFS=',' read -r -a exclude_array <<< "$exclude_list"

# Loop through all the files in the current directory
for file in *; do
  # Skip the script itself and the files in the exclude list
  if [[ "$file" != "$script_name" && ! " ${exclude_array[@]} " =~ " $file " ]]; then
    # Copy the file to the destination using scp
    scp "$file" "$destination"
  fi
done
