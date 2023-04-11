
#!/bin/bash

# Define the ASCII art
ascii_art=(
"                                                               "
"          _______  _______  _______  ______   _______  _______ "
"|\     /|(  ____ \(  ____ )(  ____ \(  __  \ (  ___  )(  ____ \\"
"| )   ( || (    \/| (    )|| (    \/| (  \  )| (   ) || (    \/"
"| (___) || (__    | (____)|| (__    | |   ) || |   | || |      "
"|  ___  ||  __)   |     __)|  __)   | |   | || |   | || |      "
"| (   ) || (      | (\ (   | (      | |   ) || |   | || |      "
"| )   ( || (____/\| ) \ \__| (____/\| (__/  )| (___) || (____/\\"
"|/     \|(_______/|/   \__/(_______/(______/ (_______)(_______/"
"                                                               "
)

# Get the terminal width and height
terminal_width=$(tput cols)
terminal_height=$(tput lines)

# Calculate the position to center the ASCII art
x_position=$(( (terminal_width - ${#ascii_art[0]}) / 2 ))
y_position=$(( (terminal_height - ${#ascii_art[@]}) / 2 ))

# Clear the terminal
clear

# Loop to create the animation effect
for i in $(seq 1 3); do
  tput cup $y_position $x_position

  # Print the ASCII art
  for line in "${ascii_art[@]}"; do
    echo -e "\033[1;${i}2m$line"
  done

  # Sleep for a short time to create the animation effect
  sleep 0.5

  # Clear the terminal
  clear
done

# Reset terminal colors
tput sgr0
