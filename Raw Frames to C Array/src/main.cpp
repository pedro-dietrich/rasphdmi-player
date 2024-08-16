#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct FrameInfo
{
    uint32_t width;
    uint32_t height;
    uint32_t bytesPerPixel;
    uint32_t pitch;
    uint32_t expectedSize;
};

bool readFile(const std::string& fileName, const FrameInfo& frameInfo, std::ofstream& outputFile);

int main(int argc, char** argv)
{
    if(argc < 5)
    {
        std::cerr << "Correct usage:\n\tbin_to_array <width> <height> <bpp> <frame_*.raw>" << std::endl;
        return -1;
    }

    FrameInfo frameInfo;

    uint32_t frameCount = argc - 4;
    frameInfo.width = std::stoi(argv[1]);
    frameInfo.height = std::stoi(argv[2]);
    uint32_t bpp = std::stoi(argv[3]);

    frameInfo.bytesPerPixel = bpp / 8;
    frameInfo.pitch = frameInfo.width * frameInfo.bytesPerPixel;
    frameInfo.expectedSize = frameInfo.pitch * frameInfo.height;

    std::ofstream outputFile{"video.data"};
    if(!outputFile)
    {
        std::cerr << "Error: Unable to create output file." << std::endl;
        return -1;
    }

    std::ostringstream start;
    start << "{\n    ";
    outputFile << start.str();

    std::string fileName;
    uint32_t progress = 0;
    uint32_t lastProgress = 0;
    std::ostringstream frameGap;
    frameGap << ",\n\n    ";

    for(uint32_t frameNumber = 1; frameNumber <= frameCount; frameNumber++)
    {
        if(!readFile(argv[frameNumber + 3], frameInfo, outputFile))
            return -1;

        if(frameNumber < frameCount)
            outputFile << frameGap.str();

        progress = (100 * frameNumber) / frameCount;
        if(progress > lastProgress)
        {
            std::cout << "\r[";
            for(uint32_t i = 0; i < 100; i++)
                std::cout << ((i < progress) ? '=' : ' ');
            std::cout << "]\t" << progress << "%";
        }
        lastProgress = progress;
    }

    std::ostringstream end;
    end << "\n};\n";
    outputFile << end.str();

    std::cout << "\nVideo data written to \"video.data\"" << std::endl;

    return 0;
}

bool readFile(const std::string& fileName, const FrameInfo& frameInfo, std::ofstream& outputFile)
{
    std::ifstream inputFile(fileName, std::ios::binary);
    if(!inputFile)
    {
        std::cerr << "Error: Unable to open file \"" << fileName << "\"." << std::endl;
        return false;
    }

    std::vector<uint8_t> fileData{std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>()};

    if(fileData.size() != frameInfo.expectedSize)
    {
        std::cerr << "Error: Expected file size does not match.\n"
            "\tExpected: " << frameInfo.width << " x " << frameInfo.height << " x " << frameInfo.bytesPerPixel << " = " << frameInfo.expectedSize << " bytes\n"
            "\tGot: " << fileData.size() << " bytes" << std::endl;
        return false;
    }

    std::ostringstream output;
    for(int i = 0; i < fileData.size(); i++)
    {
        output << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(fileData[i]);

        if(i == fileData.size() - 1)
            break;
        if(i % (frameInfo.pitch) == frameInfo.pitch - 1)
            output << ",\n    ";
        else
            output << ", ";
    }

    outputFile << output.str();

    return true;
}
