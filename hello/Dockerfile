# Use an official C++ runtime as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/myapp

# Copy the current directory contents into the container at /usr/src/myapp
COPY . /usr/src/myapp

# Compile the program
RUN g++ -o myapp hello.cpp

# Run the output program from the previous step when the container launches
CMD ["./myapp"]
