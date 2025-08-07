$U= ${halil-alagl}
build: 
	@echo "Building the project..." 
	g++ -lcpr -ljsoncpp main.cpp -o github-activity  
	@echo "Build complete." 
	./github-activity $U