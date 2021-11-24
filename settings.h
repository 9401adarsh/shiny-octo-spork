//creating a singleton class to determine default configuration for simulation.
class Settings{
    public:
        //default hopCount values for packet Object
        static const int _defaultHopCount = 4;
        //boolean to allow looping or not in flooding algorithm 
        static const bool _allowLooping = false;
};