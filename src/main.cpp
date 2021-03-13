#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

// !Accessor hack for m_Artboards
#define private public
#include "file.hpp"
#define private private

#include "no_op_renderer.hpp"
#include "animation/animation.hpp"


namespace fs = std::filesystem;

namespace rive
{
    RenderPath* makeRenderPath() { return new NoOpRenderPath(); }
    RenderPaint* makeRenderPaint() { return new NoOpRenderPaint(); }
}

// !1. The app should output the number and names of artboards in the file
// !2. The number and names of all animations
// !3. And a summary of the number of items in each artboard

int main(int argc, char *argv[])
{
    if (argc <= 1) return -1;

    // Get full path from input
    std::string inputFile = argv[argc-1];
    auto const& fullInputFilePath = fs::canonical(fs::path(inputFile));

    // Create filestream and determine size
    std::ifstream fileStream(fullInputFilePath, std::ios::in | std::ios::binary);
    auto* buffer = fileStream.rdbuf();
    std::size_t size = buffer->pubseekoff(0, fileStream.end, fileStream.in);
    buffer->pubseekpos(0, fileStream.in);

    // Read the stream into our uinque_ptr buffer
    std::unique_ptr<uint8_t[]> bytes(new uint8_t[size]);
    buffer->sgetn(reinterpret_cast<char*>(bytes.get()), size);

    // Import the rive file
    auto reader = rive::BinaryReader(bytes.get(), size);
    rive::File* file = nullptr;
    auto result = rive::File::import(reader, &file);
    
    if (result != rive::ImportResult::success) {
        std::cout << "Error importing  " << fullInputFilePath << std::endl;
        return -1;
    }
    std::cout << std::endl;
    std::cout << "Artboard Summary for " << fullInputFilePath << std::endl;
    std::cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:." << std::endl << std::endl;

    // !1. The app should output the number and names of artboards in the file
    // rive::File::m_Artboards is private to answer question 1 we will need to 
    // manually deserialize numArtboards or hack the API
    const size_t numArtboards = file->m_Artboards.size();
    std::cout << numArtboards << " Artboard(s):" << std::endl;
    for (size_t i = 0; i < numArtboards; i++)
    {
        auto icon = [](int i = 0, int max = 1) { return (i == max - 1) ? "└── " : "├── "; };
        auto seperator = [](int i = 0) { return (i == 0) ? "├──" : "│   "; };

        // Artboard index and name and object count
        std::string name = file->m_Artboards[i]->name();
        auto* artboard = file->artboard(name);
        std::cout << icon(i, numArtboards) << "[" << i << "] " << artboard->name() << ":" << std::endl;

        // !2. The number and names of all animations
        const size_t numAnimations = artboard->animationCount();
        std::cout << "    " << icon(1) << numAnimations << " Animation(s):" << std::endl;
        for (size_t j = 0; j < numAnimations; j++)
        {
            auto* anim = artboard->animation(j);
            std::cout << "    |   " << icon(j, numAnimations) << "[" << j << "] " << anim->name() << std::endl;
        }

        // !3. And a summary of the number of items in each artboard
        auto const& objects = artboard->objects();
        std::cout << "    " << icon() << objects.size() << " Objects" << std::endl;
    }

    return 0;
}
