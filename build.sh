#!/bin/bash

# Raytracer Build and Run Script
# Usage: ./build.sh [--no-sdl] [--help]

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Help function
show_help() {
    echo "Raytracer Build and Run Script"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --no-sdl    Run raytracer without SDL (headless mode)"
    echo "  --help      Show this help message"
    echo ""
    echo "This script will:"
    echo "  1. Compile the raytracer"
    echo "  2. Run the raytracer"
    echo "  3. Convert PPM output to PNG"
    echo "  4. Display file information"
}

# Parse command line arguments
SDL_FLAG=""
if [[ "$1" == "--no-sdl" ]]; then
    SDL_FLAG="--no-sdl"
elif [[ "$1" == "--help" ]]; then
    show_help
    exit 0
fi

# Check if required tools are available
check_dependencies() {
    
    if ! command -v g++ &> /dev/null; then
        print_error "g++ compiler not found. Please install build-essential."
        exit 1
    fi
    
    if ! pkg-config --exists sdl2; then
        print_warning "SDL2 development libraries not found. SDL mode may not work."
    fi
    
    if ! command -v convert &> /dev/null; then
        print_warning "ImageMagick not found. Will skip PNG conversion."
        print_status "To install ImageMagick: sudo apt install imagemagick"
    fi
    
}

# Create output directory if it doesn't exist
create_output_dir() {
    if [ ! -d "output" ]; then
        print_status "Creating output directory..."
        mkdir -p output
    fi
}

# Compile the raytracer
compile_raytracer() {
    
    g++ main.cpp -lSDL2 -o raytracer -O3 -std=c++11

}

# Run the raytracer
run_raytracer() {
    
    if [ -n "$SDL_FLAG" ]; then
        ./raytracer --no-sdl
    else
        print_status "Running with SDL graphics"
        print_warning "If this fails with graphics errors, try: $0 --no-sdl"
        ./raytracer
    fi
    
    if [ $? -eq 0 ]; then
        print_success "Raytracer execution completed"
    else
        print_error "Raytracer execution failed"
        exit 1
    fi
}

# Convert PPM to PNG
convert_to_png() {
    if [ -f "output/output.ppm" ]; then
        if command -v convert &> /dev/null; then
            if convert output/output.ppm output/output.png; then
                print_success "PNG conversion completed"
            else
                print_warning "PNG conversion failed"
            fi
        else
            print_warning "ImageMagick not installed. Skipping PNG conversion."
            print_status "To install: sudo apt install imagemagick"
        fi
    else
        print_error "PPM file not found at output/output.ppm"
    fi
}


# Main execution
main() {
    echo "Raytracer Build Script"
    check_dependencies
    create_output_dir
    compile_raytracer
    run_raytracer
    convert_to_png
}

# Run main function
main "$@"
