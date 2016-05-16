#include <iostream>
#include <fstream>
#include <string>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/communication/communication.hpp>


int main(int argc, char * argv[]) {
    rapp::robot::info info(argc, argv);
    rapp::robot::communication comm(argc, argv);
    
    comm.text_to_speech("Think of a number between 1 and 100. When ready, please say the word start.");
    
    // create list of words for recognition
    std::vector<std::string> words;
    // add two words
    words.push_back("start");
    words.push_back("stop");
    std::string result;


    // start word spotting until proper word will be recognized
    do {
        result = comm.word_spotting(words);

        // if player wants to end the game
        if (result == "stop") {
            comm.text_to_speech("I hope we will play again soon!");
            return 0;
        }

        // notify human 
        if (result != "start") {
            comm.text_to_speech("Say start when ready or stop if you want to finish game.");
        }
    } while (result != "start");
    
    
    // create variables for lower and upper limit
    int lower = 1;
    int upper = 100;

    // prepare new list of words
    words.clear();
    words.push_back("yes");
    words.push_back("no");
    words.push_back("stop");

    // loop until both limits are equal
    while(lower < upper) {
        // calculate middle number
        int middle = lower + (upper - lower) / 2;
        // prepare question
        std::string question;
        question += "Is your number greater than " + std::to_string(middle) + "?";
        // ask the question
        comm.text_to_speech(question);
        // wait for an answer
        do {
            result = comm.word_spotting(words);

            // if player wants to end the game
            if (result == "stop") {
                comm.text_to_speech("I hope we will play again soon!");
                return 0;
            }

            // notify human 
            if (result != "yes" && result != "no") {
                comm.text_to_speech("Yes or no!");
            }
        } while (result != "yes" && result != "no");

        // if the number is greater
        if (result == "yes") {
            lower = middle + 1;
        }
        // if the number is lower or equal
        if (result == "no") {
            upper = middle;
        }
    }
    
    
    std::string text = "I know the answer! ";
    text += "You thought about " + std::to_string(lower);
    comm.text_to_speech(text);
    
    
    comm.play_audio(info.get_path("share/talk_to_me/cheer.wav"));
    
    
    
    return 0;
}
