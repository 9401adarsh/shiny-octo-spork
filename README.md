# Flooding Routing Algorithm Simulation - C++

## Summary: 

The following repository consists of a simple dialog for the simulation of flooding routing algorithm with a solution to overcome looping. The language used is C++. 

The solution implemented to overcome looping: 
    At each node (router), keep track of seen packets and only forward each packet only once.  

<br />


## File Structure
- settings.h : Header file to set Default Values in Simulation - HopCount (int) for Packet, Allow Looping (boolean) for controlled flooding    
- packet.h : Header file for packet class
- router.h : Header file for router class
- driver.cpp : The file in which network topology, packets are constructed and run for simulation. 

<br />

## Instructions to Run: 
Setting up input file, under project directory make `input.in` according to `input-format.txt`
```
<number of routers>
[next 'num of routers' lines]
<addresses of router>
[end of router]
<number of edges>
[for each edge Ri - Rj]
<address of router-i>
<address of router-j>
[end edges]
<number of Packets>
[for each packet pi]
<payload>
<destination router address>
[end packets]
``` 

In project directory, on terminal run: 
```
g++ settings.h packet.h router.h
g++ driver.cpp -o driver

//Show output on terminal
./driver 

//Redirect output to a file output.out
./driver > output.out
```

<br />

## Default Configuration: 
- **Default mode is controlled flooding.**

- **For uncontrolled flooding, with looping. In settings.h, change line 7 to, and recompile**
```
        static const bool _allowLooping = true;
```
- **Default hop count value is 4. To change, goto line 5 in settings.h and change. Recompile for changes to reflect.**
```
        static const int _defaultHopCount = <new_Value>;
```



