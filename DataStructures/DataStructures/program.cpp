/*
#include "hash_map.hpp"
#include "menu.hpp"
#include "file_reader.hpp"
#include <iostream>
#include <sstream>

void run()
{
	std::string filename;
    std::string encoding_method = "line count";
	menu menu;

    data_structures::HashMap<std::string, int> compressedMap(101, std::hash<std::string>{});

	while (true)
	{
		menu.ShowMenu();
		int choice = menu.GetMenuChoice();

        if (choice == 4)
            break;

        if (choice == 1)
        {
            std::cout << "Enter FileName: ";
            std::cin >> filename;

            try
            {
                FileReader reader(filename);
                std::string line;

                while (reader.ReadLine(line))
                {
                    if (line.empty() || std::all_of(line.begin(), line.end(), isspace))
                        continue; 
                    compressedMap[line] = compressedMap[line] + 1;
                }

                reader.Close();

                std::cout << "File compressed successfully." << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cerr << "File error: " << e.what() << std::endl;
            }
        }

        else if (choice == 2)
        {
            std::cout << "Compressed form (line counts):\n";
            auto keys = compressedMap.Keys();
            for (size_t i = 0; i < keys.size(); ++i)
            {
                try
                {
                    const std::string& word = keys[i];
                    int count = compressedMap[word];
                    std::cout << word << ": " << count << "\n";
                }
                catch (const data_structures::AdtException& e)
                {
                    std::cerr << "Error retrieving value: " << e.what() << "\n";
                }
            }
        }

        else if (choice == 3)
        {
            if (filename.empty())
            {
                std::cout << "No file loaded yet. Please load a file first (option 1).\n";
                continue;
            }

            // Toggle encoding method
            if (encoding_method == "line count")
            {
                encoding_method = "word count";
            }
            else
            {
                encoding_method = "line count";
            }

            std::cout << "Switched to " << encoding_method << " compression.\n";

            // Reload and recompress the file with the new encoding method
            compressedMap.Clear();

            try
            {
                FileReader reader(filename);
                std::string line;

                if (encoding_method == "line count")
                {
                    while (reader.ReadLine(line))
                    {
                        if (line.empty() || std::all_of(line.begin(), line.end(), isspace))
                            continue;
                        compressedMap[line] = compressedMap[line] + 1;
                    }
                }
                else if (encoding_method == "word count")
                {
                    while (reader.ReadLine(line))
                    {
                        if (line.empty() || std::all_of(line.begin(), line.end(), isspace))
                            continue;
                        std::istringstream iss(line);
                        std::string word;
                        while (iss >> word)
                        {
                            compressedMap[word] = compressedMap[word] + 1;
                        }
                    }
                }

                reader.Close();
                std::cout << "File recompressed successfully with encoding method: " << encoding_method << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cerr << "File error: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid choice, please try again.\n";
        }
    }
}

*/

int main()
{
	//run();
	return 0;
}