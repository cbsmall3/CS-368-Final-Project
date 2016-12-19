


#include "AsTheCrowFlies.h"



AsTheCrowFlies::AsTheCrowFlies(){}

int AsTheCrowFlies::menu (char* filename) throw(std::exception) { //REVISED
  
  bool done = false;
  
  main_city_list=processCityData(filename);	
  
  Graph new_graph(main_city_list);
  
  mainGraph.setGraph(new_graph.getGraph());
  
  
  do {
    
    cout << "\nAs The Crow Flies" << endl;
    cout << std::endl;
    
    
    //The data field boolean variable 'done' and the do-while loop ensure
    //that the menu function continues to execute until the user exists the
    //program
    
    
    
    
    cout << "\n1. Load your cities from a file\n2. Display available cities\n3. Create a trip\n4. Add a city to available cities\n5. Find shortest path between two cities\n6. Print text version of map of cities\n7. Exit program" << "\nEnter choice as integer [1-7]: "<<endl;
    
    //'i' represents the user's menu choice
    
    string choice;
    int i = 0;
    
    //The local boolean variable 'continueInput' ensures inner do-while
    //loop continues until the user has entered a valid menu choice
    
    bool continueInput = true;
    
    bool leave = false;
    
    
    
    //Accepts menu choice from user and keeps prompting the user
    //to enter a choice if the entry is invalid
    
    do {
      
      
      cin.clear();
      choice.clear();	
      
      getline(cin,choice);
      
      if (choice.empty() && !leave) {
        
        cout << "\nNo value entered. Please enter a selection:" << endl;
        cin.clear();
        choice.clear();
        leave = true;
        
        
        
      } else if(choice.empty() && leave) {
        
        cout<<"\nWould you like to exit this application? Enter 'y' if yes: " << endl;
        cin.clear();
        choice.clear();
        getline(cin,choice);
        if(choice=="y"||choice=="Y") {
          
          continueInput=false;
          i=7;
          
        } else {leave = false;}
        
        
        
      }
      
      
      if(continueInput || !leave) {
        
        if (is_int(choice)) {
          
          i = std::stoi(choice);         
          
          if(i <= 7 && i >= 1) {
            
            continueInput = false;
            leave = true;           
            
          } else {  
            
            std::cout << "\nSelection out of range! Please input a correct value." << endl;
            cin.clear();
            choice.clear(); 
            i = 0;  
            
          }  
          
        } else {
          
          if(!choice.empty()) {
            std::cout << "\nNot a number! Please input a correct value." << endl;
            cin.clear();
            choice.clear();   
            i = 0;
          }
          
        }
        
      }
      
    } while(continueInput || !leave);
    //gets user menu input
    
    
    
    
    switch (i)
    {
      
    case 1: //Allows user to add a list of cities to the current list or replace the current list with their list
      
    {
      
      bool quit = false; //used to end task if user indicates
      bool add = false; //used to add new city list to current one if user indicates
      string filename, temp;
      
      do {
        
        cout << "\nEnter a filename: ";
        
        getline(cin, filename);
        
        if(filename.empty()) {
          
          std::cout<<"\nNo filename enetered. If you want to quit, enter 'q' now"<<std::endl;
          cin.clear();
          getline(cin,filename);
          
          if(filename=="q"||filename=="Q") { 
            
            quit = true ;
            
          }
          
        }
        
      } while(!quit && filename.empty());
      
      if(!quit) {
        
        std::cout<<"\nIf you want to add your list of cities to the current one instead of replacing it, enter 'y'"<<std::endl;
        
        cin.clear();
        getline(cin,temp);
        
        if (temp=="y"||temp=="Y") {
          
          add=true;
          
        }
        
        
        
        if(add) {	
          
          main_city_list = processCityData(filename.c_str(), main_city_list); //user cities ADDED to current list
          
        } else {
          
          main_city_list = processCityData(filename.c_str());
          
          Graph new_graph(main_city_list);
          
          mainGraph.getGraph().clear();
          
          mainGraph.setGraph(new_graph.getGraph());
          
          
          } //user cities REPLACES current list

        printf("\nCity list is updated. For a print-out of the new list, please use option 2\n");
        
        }
      

      
      break;
      
    }
      
    case 2: //Prints out cities on current list

      std::cout<<"\nThere are " <<main_city_list.size() <<" cities on the list:\n"<<std::endl;	      
      
      for (Vertex v : main_city_list)
      {
        
        std::cout << v.getName() <<","<< v.getLatitude() << "," << v.getLongitude() << std::endl;
      }
      cout << endl;
      
      
      break;
      
    case 3://Allows user to input a list of cities to visit
      createTrip();
      break;
      
    case 4: //Allows user to add (an) individual (city) cities
      addCity();
      break;
      
    case 5: //Allows user to input a start and stop city and then display the shortest route between them

     printf("\nThis method will find the shortest path between two cities if one exists. Please follow the prompts to continue.\n");
      
     minPathTrip = findShortestPath();  	    
      
     int total,curr;
      total = 0;
      curr = 0;
      
      if(minPathTrip.size()>1) {
        
        std::cout<<"\nMinimum distance path is:\n"<<std::endl;
        
        for (int i = 0; i < minPathTrip.size()-1; i++)
        {
          curr=findMinDistance (minPathTrip[i].getLatitude(),minPathTrip[i].getLongitude(),
                                minPathTrip[i+1].getLatitude(), minPathTrip[i+1].getLongitude())*31/50000;
          
          std::cout<< " From: " << minPathTrip[i].getName()  << " To: " << minPathTrip[i+1].getName() << " Dist:~  " << curr  <<" miles." << std::endl;
          
          total+=curr;
        }
        //std::cout << std::endl;
        
        std::cout<<"\nTotal Distance for the Trip is:\n"<< total << " miles." << std::endl;
        
        //std::cout << std::endl;
        
      } else if(minPathTrip.size()==1) {

	 std::cout<<"\nStart and ending city are the same.\nPlease try again using different city names for each entry.\n"<<std::endl; 
	
      } else {std::cout<<"\nNo cities to print\n"<<endl;} 
      
      
      break;
      
      
    case 6://Displays text representation of mapping between the cities
      
      mainGraph.printGraph();
      break;
      
    case 7: //Writes current list to file and then terminates the program
      
      
      writeCitiesList("available_cities.txt");
      cout << "\nThank you for your business.\nSaved available cities to available_cities.txt\n" << endl;
      main_city_list.clear();
      mainGraph.getGraph().clear();
      minPathTrip.clear();
      user_city_list.clear();
      done = true;
      break;
      
      
    default:
      
      break;
    
    }
    
    
    
    
  } while(!done);
  
  
  
  return 0; 
  
}



bool AsTheCrowFlies::is_int(const std::string& s) {
  
  std::istringstream iss(s);
  int d;
  char c;
  return iss >> d && !(iss >> c);
}



bool AsTheCrowFlies::is_double(const std::string& s) {
  
  std::istringstream iss(s);
  double d;
  char c;
  return iss >> d && !(iss >> c);
}



std::vector<std::string> AsTheCrowFlies::split(const std::string &s, const char delim) {
  
  std::vector<std::string> elems;
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  
  return elems;
  
}



std::vector <Vertex> AsTheCrowFlies::processCityData (const std::string &filename) throw(std::exception) { //REVISED
  
  vector <Vertex> city_data; //return value for function
  double latValue, longValue; // Holds validated latitude & longitude values //
  bool stop=false; //used to control loading of city data
  bool done = false;
  char delim = ','; //split pt
  vector<std::string> lines; //holds pre-split lines
  string line; //each input line read from input file
  string token;
  ifstream myStream; //input file stream
  
  myStream.open(filename.c_str());
  
  if(!myStream.is_open()) {
    cout << "\nCouldn't open the text file\n" << endl;
    if (city_data.size()<1) {
      return main_city_list;
    } else {
	
	return city_data;

    }
   
  }
  
  
  while (getline(myStream,line)) {
    
    lines.push_back(line);
    
    
  }
  
  for (std::string s : lines) {	
    
    vector <std::string> input=split(s,delim);
    
    
    
    
    
    //The nested for loops below check each line entry to ensure
    //the data are the correct type and range and that it has each
    //required element
    
    
    
    if (input.size() != 3) {
      
      stop = true;
      
      
    } else {
      
      
      if(!(is_double(input[1]))||latValue < -180.0 || latValue > 180.0) {
        
        stop=true;		
        break;
        
        
      } else {latValue = std::stod(input[1]);}
      
      
      if(!(is_double(input[2]))||longValue < -180.0 || longValue > 180.0) {
        
        stop=true;
        break;
        
        
      } else {longValue = std::stod(input[2]);}
      
    }
    
    
    
    
    if(!stop) {
      
      Vertex newCity(input[0],latValue,longValue);

      if(done) {done = false;}
      
      //Check if the newly entered city is on the list and if not...
      
      for (auto it = city_data.begin(); it!=city_data.end() && !done; ++it) {
        
        
        if(*it == newCity) {
          
          done = true;
          
        }
        
      }
      
      //...add it to the output city list and update the graph
      
      if (!done) {
        
        city_data.push_back(newCity);
        mainGraph.insert(newCity);
        
      }

      
      
    } else {stop=false;}
    
 }
  
  
  return city_data;
  
  
  
  
} 


std::vector <Vertex> AsTheCrowFlies::processCityData (const std::string &filename, std::vector<Vertex> prev_list) throw(std::exception) { //REVISED
  
  
  printf("\nEntered add to list method\n");
  
  std::vector <Vertex> city_data = prev_list; //return value for function
  double latValue, longValue; // Holds validated latitude & longitude values //
  bool stop=false; //used to control loading of city data
  bool done = false; //used to control loading of new city Vertex after duplicate check
  char delim = ','; //split pt
  vector<std::string> lines; //holds pre-split lines
  string line; //each input line read from input file
  ifstream myStream; //input file stream
  
  myStream.open(filename.c_str());
  
  if(!myStream.is_open()) {
    cout << "\nCouldn't open the text file\n" << endl;
        if (city_data.size()<1) {
      return main_city_list;
    } else {
	
	return city_data;

    }  

}
  
  
  while (getline(myStream,line)) {
    
    lines.push_back(line);
    
  }
  
  for (std::string s : lines) {	
    
    vector <std::string> input=split(s,delim);
    
    //The nested for loops below check each line entry to ensure
    //the data are the correct type and range and that it has each
    //required element
    
    
  if (input.size() != 3) {
      
      stop = true;
      
    } else {
      
      
      if(!(is_double(input[1]))||latValue < -180.0 || latValue > 180.0) {
        
        stop=true;		
        break;
        
      } else {latValue = std::stod(input[1]);}
      
      
      if(!(is_double(input[2]))||longValue < -180.0 || longValue > 180.0) {
        
        stop=true;
        break;
        
        
      } else {longValue = std::stod(input[2]);}
      
    }
    
    
    
    
    if(!stop) {
      
      Vertex newCity(input[0],latValue,longValue);
      
      if(done) {done = false;}
      
      //Check if the newly entered city is on the list and if not...
      
      for (auto it = city_data.begin(); it!=city_data.end() && !done; ++it) {
        
        
        if(*it == newCity) {
          
          done = true;
          
        }
        
      }
      
      //...add it to the output city list and update the graph
      
      if (!done) {
        
        city_data.push_back(newCity);
        mainGraph.insert(newCity);
        
      }
      
    } else {stop=false;}
    
  }
  
  
  return city_data;
  
  
  
  
} 




void AsTheCrowFlies::addCity() throw(std::exception) {
  
  bool stop = false;
  
  do {
    
    
    //Prompts user to enter city name. Will reprompt
    //if nothing entered
    
    
    bool done = false;
    bool leave = false;
    std::string city, xString;
    double newLatitude, newLongitude;
    
    
    while (!done && !stop) {
      
      std::cout << "\nEnter city name: " << std::endl;
      getline(cin, xString);
      if (xString.empty() && !leave) {
        
        cout << "\nNo city name entered. Please enter a city name." << endl;
        cin.clear();
        xString.clear();
        leave=true;
        
        
      } else if(xString.empty() && leave) {
        
        cout<<"\nWould you like to exit this application? Enter 'y' if yes. " << endl;
        
        cin.clear();
        city.clear();
        getline(cin,xString);
        if(xString=="y"||xString=="Y") {
          
          stop=true;
          done=true;
          
        } else {leave = false;}
        
      } else {
        
        city=xString;
        done = true;
      }
      
      
    }
    
    
    
    cin.clear();
    done = false;
    if(leave) {leave = false;}
    xString.clear();
    
    
    
    //Prompts user to enter latitude. Will reprompt if
    //nothing entered, latitude is out range or not a number
    
    
    while (!done && !stop) {
      
      std::cout << "\nEnter latitude as double (-180.0 to 180.0): " << std::endl;
      
      getline(cin, xString);
      
      if (xString.empty() && !leave) {
        
        cout << "\nNo value entered. Please enter a latidue." << endl;
        cin.clear();
        xString.clear();
        leave=true;
        
        
      } else if(xString.empty() && leave) {
        
        cout<<"\nWould you like to exit this application? Enter 'y' if yes. " << endl;
        cin.clear();
        xString.clear();
        getline(cin,xString);
        if(xString=="y"||xString=="Y") {
          
          stop=true;
          done=true;
          
        } else {leave = false;}
        
      } else {
        
        if (is_double(xString)) {
          
          newLatitude = std::stod(xString);
          
          if(newLatitude <= 180.0 && newLatitude >= -180.0) {
            
            done = true;
            
          } else {  
            
            std::cout << "\nLatitude out of range! Please input a correct value." << endl;
            cin.clear();
            xString.clear();   
            
          }  
          
        } else {
          
          std::cout << "\nNot a number! Please input a correct value." << endl;
          cin.clear();
          xString.clear();
          newLatitude = 0.0;   
          
        }
        
      }
      
    }
    
    
    
    done = false;
    if(leave) {leave = false;}	
    cin.clear();
    xString.clear();
    
    
    //Prompts user to enter longitude. Will reprompt if
    //nothing entered, longitude is out range or not a number
    
    while (!done && ! stop) {
      
      
      
      std::cout << "\nEnter longitude as double (-180.0 to 180.0): " << std::endl;
      
      getline(cin, xString);
      
      if (xString.empty() && !leave) {
        
        cout << "\nNo value entered. Please enter a longitude." << endl;
        cin.clear();
        xString.clear();
        leave=true;
        
        
      } else if(xString.empty() && leave) {
        
        cout<<"\nWould you like to exit this application? Enter 'y' if yes. " << endl;
        cin.clear();
        xString.clear();
        getline(cin,xString);
        if(xString=="y"||xString=="Y") {
          
          stop=true;
          done=true;
          
        } else {leave = false;}
        
        
        
      } else {
        
        if (is_double(xString)) {
          
          newLongitude = std::stod(xString);
          
          if(newLongitude <= 180.0 && newLongitude >= -180.0) {
            
            done = true;
            
          } else {  
            
            std::cout << "\nLongitude out of range! Please input a correct value." << endl;
            cin.clear();
            xString.clear();
            newLongitude = 0.0;   
            
          } 
          
        } else {
          
          std::cout << "\nNot a number! Please input a correct value." << endl;
          cin.clear();
          xString.clear();   
          newLongitude = 0.0;
          
        }
        
      }
      
    }
    
    
    
    //Create new city object and enter data
    
    
    
    if(done && !stop) {
      
      Vertex new_city(city,newLatitude,newLongitude);
      
      if(done) {done = false;}
      
      //Check if the newly entered city is on the list and if not...
      
      for (auto it = main_city_list.begin(); it!=main_city_list.end() && !done; ++it) {
        
        
        if(*it == new_city) {
          
          done = true;
          
        }
        
      }
      
      if (!done) {
      
        main_city_list.push_back(new_city);
        mainGraph.insert(new_city);
        user_city_list.push_back(new_city);
        std::cout << "\nAdded: " << new_city.getName() <<", "<< new_city.getLatitude() << ", " << new_city.getLongitude() << std::endl;
      
      }
      
      //...add new city to user's city list, update the graph and print out new city data
      
      //Ask user if they want to enter a new city. If not leave outermost do-while loop
      
      cout<<"\nWould you like to add another city? Enter 'y' if yes. " << endl;
      cin.clear();
      xString.clear();
      getline(cin,xString);
      
      if(!(xString=="y"||xString=="Y")) {stop = true;} 
      
      if (!stop) {done=stop;}
      
      
      //Save user cities to standard file
      
      ofstream myStream("cities_added.txt");
      
      if (!myStream.is_open()) {
        cerr << "\nCouldn't open the file cities_added.txt" << endl;
      }
      // The commas act as delimiters//
      for (Vertex v : user_city_list) {
        std::string s = v.getName() + ", " + to_string(v.getLatitude()) + ", " + to_string(v.getLongitude());
        myStream << s <<"\n"; 
      }
      
     }
    
    } while(!stop);  
  
  } 


void AsTheCrowFlies::writeCitiesList(const std::string &filename) throw(std::exception) {
  
  try {
    ofstream out;
    out.open(filename.c_str());
    if(!out.is_open()) {
      cerr << "\nCouldn't open the file" << endl;
    }
    // The commas act as delimitters//
    for (Vertex v : main_city_list) {
      std::string s = v.getName() + ", " + to_string(v.getLatitude()) + ", " + to_string(v.getLongitude());
      out << s <<"\n";
    }
    
    
    
  } catch (std::exception &FileNotFoundException) {
    std::cout << "\nUnable to read file\n" << std::endl;
    exit(1);
  }
  
  
}



void AsTheCrowFlies::createTrip() throw(std::exception) {
  
  
  bool done = false;
  bool end = false;
  
  do {
    
    std::vector<Edge> tripList;
    bool stop = false;
    
    
    cout << "There are " << main_city_list.size() << " cities to choose " << "from." << endl;
    
    
    if (user_city_list.size() > 0)
    {
      
      cout << "Add to current trip (y/n) ?" << endl;
      
      string choice;
      
      getline(cin, choice);
      if (!(choice=="y"||choice=="Y")) {
        
        user_city_list.clear();
        cout << "\nThere are " << main_city_list.size() << " cities to choose " << "from." << endl;
        cout << "New trip created, needs at least two cities" << endl;
      
      }
    } 
    
    //The while loop controls user entry and new city count
    
    bool cityEntered = true;
    
    
    while (cityEntered)
    {
      
      cout << "\nEnter next city name (or enter to end) : " << endl;
      std::string temp;
      getline(cin,temp);
      
      if(temp.empty()) {
        
        cout<<"You did not enter a city name. Are you sure you want to quit? If so, enter 'Y' or 'y', otherwise enter a city name "<<endl;
        cin.clear();
        temp.clear();
        getline(cin,temp);
        
        if(temp=="y"||temp=="Y") {
          
          cityEntered = false;
          stop = true;
          end = true;
          break;
          
        }
        
      } else {
        
        if(stop) {stop = false;}
        
        for (int i = 0; i < main_city_list.size() && !stop; i++) {
          
          if (main_city_list[i].getName()==temp) {
            user_city_list.push_back(main_city_list[i]);
            stop = true;
          }
        }
      }
    }
    
    //The if loop ensures there two or more valid cities entered above
    //before the string of cities is split and loaded into the string array
    
    
    if (user_city_list.size() > 1)
    {
      
      Vertex start, stop;
      
      cout << "\nThere are " << user_city_list.size() << " cities in" << " this trip.\n" << endl;
      
      
      
      for (int i = 0; i < user_city_list.size()-1; i++) {
        
        double dist;
        
        dist = findMinDistance(user_city_list[i].getLatitude(),user_city_list[i].getLongitude(),user_city_list[i+1].getLatitude(),user_city_list[i+1].getLongitude());
        
        Edge edge(user_city_list[i],user_city_list[i+1],dist);					  			
        
        tripList.push_back(edge);
        
      }
      
      int totalDist = 0;

      for (int k = 0; k < tripList.size(); k++) {
        
        start = tripList[k].getOrigin();
        
        stop = tripList[k].getDestination();
        
        cout << "From: " << start.getName() << " To: " << stop.getName() << " " << ( tripList[k].getDistance() ) * 31 / 50000 <<  " miles"<<std::endl;
        
        totalDist += tripList[k].getDistance();
      }
      
      cout << "\nTotal Distance: " << totalDist << " meters (~" << totalDist * 31 / 50000 << " miles)" << endl;
      
      cout << "\nWrite trip details to file [y/n} ? " << endl;
      string save; 
      getline(cin, save);
      
      if (save=="y"||save == "Y") {
        
        done = false;
        
      } else {done = true;}
      
      if(done) {end=done;} //ensures do-while terminated so function terminates as well
      
      while(!done) {
        
        string tripFileName;
        
        cout << "\nEnter filename: " << endl;
        
        getline(cin, tripFileName);
        
        if (tripFileName=="\n"||tripFileName=="") {
          
          cout<<"\nThat was a not a valid file name. Please try again. If you want to try again, please select 'y' or 'Y' "<<endl;
          
          cin.clear();
          
          tripFileName.clear();                      
          
          getline(cin, tripFileName);
          
          if(tripFileName=="y"||tripFileName=="Y") {
            
            done=end=true;
            
          } else {
            
            cin.clear();
            tripFileName.clear();		
            
          }
          
        } else {
          
          ofstream out;
          
          out.open(tripFileName.c_str());
          
          if(!out.is_open()) {
            cout << "Couldn't write to the file" << endl;
            return;
          } 

          int totalDist = 0;
          
          for(int k = 0; k < tripList.size(); k++) {
            
            start=tripList[k].getOrigin();
            stop=tripList[k].getDestination();
            totalDist += tripList[k].getDistance();
            out << "From "<< start.getName() << " to " << stop.getName() <<" is "<< (tripList[k].getDistance()) * 31 / 50000 <<  " miles" << "\n";
            
            }

          out << "\nTotal Distance: " << totalDist << " meters (~" << totalDist * 31 / 50000 << " miles)" << "\n";

          done=end=true;
          
        }
        
      }
      
      
      }
    
    
    else if(!end) {
      cout << "\nMust have at least 2 cities in a trip. Did you want to continue? If not, please select 'n' or 'N' " << "" << endl;
      
      string str;
      
      getline(cin, str);
      
      if(str=="n"||str=="N") {end = true;}
      
      cout<<endl;
      
    } 
    
  } while(!end);
  
  
  return;
  
  
} 




double AsTheCrowFlies::findMinDistance(double latStart, double longStart, double latEnd, double longEnd) { //REVISED
  
  
  double x, y, z, a;
  
  
  latEnd = PI * latEnd/180;
  latStart = PI * latStart/180;
  longEnd = PI * longEnd/180;
  longStart = PI * longStart/180;
  y = pow(sin((latEnd - latStart) / 2), 2);
  z = pow(sin((longEnd - longStart) / 2), 2);
  x = y + cos(latEnd) * cos(latStart) * z;
  a = atan2(sqrt(x), sqrt(1 - x));
  return 2 * EARTH_RADIUS * a;
}

 std::deque <Vertex> AsTheCrowFlies::findShortestPath() { //NEW
  
  std::deque <Vertex> path; //return value; may be empty
  
  bool stop = false; //causes function to end if user indicates
  
  bool done = false; //ends entry loop
  
  std::string temp; //temporary string value for city name
  
  Vertex origin, target,curr; //start Vertex and stop Vertex respectively

  int start,end,size;
  
  
  //Prompt user to enter starting city
  
  while(!done && !stop) {
    
    cout << "\nEnter starting city name (or enter to end) : " << endl;
    
    getline(cin,temp);
    
    //If the user does not enter anything check to see if they want to quit...
    //...and set done and stop to true if the user requests it
    
    if(temp.empty()) {
      
      cout<<"\nYou did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y' "<<endl;
      
      cin.clear();
      temp.clear();
      
      getline(cin,temp);
      
      if(temp=="y"||temp=="Y") {
        
        done = true;
        stop = true;
        
        
      } 
      
    } else {
      
      //For valid entries, see if it matches a city on the main list...
      
      for (int i = 0; i < main_city_list.size() && !done; i++)
        
      {
        if (main_city_list[i].getName()==temp) //..if it does set origin to this city else...
        {
          
          done = true;
          origin = main_city_list[i];
          start = i;
          
        }
      }
      
      if (!done) { //...reprompt user if no matching city name and give them the option of exiting the function again
        
        std::cout<<"\nThere was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
        
        cin.clear();
        temp.clear();
        
        getline(cin,temp);
        
        if(temp=="n"||temp=="N") {
          
          done = true;
          stop = true;
          
          
        }
      }
      
    }
    
  } 
  
  if(stop) //If user indicated that they want to terminate input return empty path
    return path;
  
  //reset values for destination city and repeat same process as above
  done = false;
  temp.clear();
  cin.clear();
  
  while(!done && !stop) { 
    
    cout << "\nEnter destination city name: " << endl;
    
    getline(cin,temp);
    
    if(temp.empty()) {
      
      std::cout<<"\nYou did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y' "<<std::endl;
      
      cin.clear();
      temp.clear();
      
      getline(cin,temp);
      
      if(temp=="y"||temp=="Y") {
        
        done = true;
        stop = true;
        
      }
      
    } else {
      
      for (int i = 0; i < main_city_list.size() && !done; i++)
      {
        if (main_city_list[i].getName()==temp)
        {
          
          done = true;
          target = main_city_list[i];
          end = i;
          
        }
      }
      
      
      
      if (!done) { //...reprompt user if no matching city name and give them the option of exiting the function again
        
        
        std::cout<<"\nThere was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
        
        cin.clear();
        temp.clear();
        
        getline(cin,temp);
        
        if(temp=="n"||temp=="N") {
          
          done = true;
          stop = true;
          
        }
        
      }
      
    }
  } 
  
  
  
  if (stop) {return path;}


size = main_city_list.size(); //So I do not have to use 'main_city_list.size()' as much

//2D array for the distances between Vertex objects
std::vector <std::vector <double>> dist (size, std::vector <double> (size)); 

//2D array for closest Vertex from one Vertex to another
std::vector <std::vector <int>> next (size, std::vector <int> (size));


/* The for loops below initializes next and dist 2D arrays prior to
 *  to mapping traveral. Any Vertex objects with an Edge have the
 *  distance and destination Vertex mapped to them while all
 *  other Vertices are marked as 'INFINITY' and 'null'
 */


for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
    
      
      dist[i][j]=INFINITY;
      
    }
  
  
}

/*for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
   
     if(i==j) {dist[i][j]=0;}
    
	}
      }

dist[0][0]=0;

for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
   
     if(i==j) {next[i][j]=j;}
    
	}
      }

next[0][0]=0;*/

/*std::cout<<"\n\n After declaring and initializing the 2D array 'dist' looks like this:\n" << std::endl;


for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {

    if(dist[i][j]!=INFINITY) {
      
      std::cout << " " << dist[i][j] << " ";
      
    } else {
      
      std::cout <<" "<< dist[i][j] <<" ";
      
    }

  }
  
  
  std::cout << std::endl;
  
}


std::cout<<"\n and the 2D array 'next' looks like this:\n" << std::endl;

for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
    
    if(!next[i][j]) {
      
      std::cout << " null ";
      
    } else {
      
      std::cout << " " << next[i][j] << " ";
      
    }
    
  }
  
  
  std::cout << std::endl;
  
}*/

for (int i = 0; i < size; i++) {
  
  std::vector<Edge> edges = findEdges(main_city_list[i]);
  
  for (int j = 0; j < size; j++) {
    
    for(auto it = edges.begin(); it!=edges.end(); ++it) {
      
      if(it->getDestination()==main_city_list[j]) {
        
        dist[i][j] = it->getDistance();
        next[i][j] = j;
        
        }
      
      }
    
    }
  
  }

/*std::cout<<"\n After secondary initialization the 2D array 'dist' looks like this:\n" << std::endl;


for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
    
      
      std::cout << " " << dist[i][j] << " ";
    
    }
  
  
  std::cout << std::endl;
  
}


std::cout<<"\n and the 2D array 'next' looks like this:\n" << std::endl;

for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
    
    if(!next[i][j]) {
      
      std::cout << " null ";
      
    } else {
      
      std::cout << " " << next[i][j] << " ";
      
    }
    
  }
  
  
  std::cout << std::endl;
  
}*/




 //The three nested for loops are used to check whether two adjacent Vertices have a shorter path
//between them by compairing with each and the current minimum distance and if a shorter path
 //is found, the distance and adjacent Vertices are updated


for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
    for (int k = 0; k < size; k++) {
	
	if(dist[i][j]>dist[k][j]+dist[i][k]){

		dist[i][j] = dist[k][j]+dist[i][k];
		next[i][j] = next[i][k];

        }
	
     }
   }
}

/*std::cout<<"\n After shortest path traversal the 2D array 'dist' looks like this:\n" << std::endl;


for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
  
      
      std::cout << " " << dist[i][j] << " ";
      
    }
  
  
  std::cout << std::endl;
  
}


std::cout<<"\n and the 2D array 'next' looks like this:\n" << std::endl;

for (int i = 0; i < size; i++) {
  
  for (int j = 0; j < size; j++) {
    
    if(!next[i][j]) {
      
      std::cout << " null ";
      
    } else {
      
      std::cout << " " << next[i][j] << " ";
      
    }
    
  }
  
  
  std::cout << std::endl;
  
}*/



//Checks if common path is present from start to end and advises if there is not one and returns empty path
if(!next[start][end]) {
	
	return path;

}

curr = origin; //current tracking node set to origin node

path.push_back(curr); //current tracking node loaded onto end of path deque

while (start!=end && start < size && start >= 0) { //while loops keeps adding nodes until it reaches the end node

       
 
        start = next[start][end]; //current node updated

	     

	    if(start>=size || size < 0) { //if current node is naught, function terminates
	
	       start = end;	

	    } else {


             path.push_back(main_city_list[start]);    //new current node added to end of dequeue

        }

}



return path;

}




std::vector<Edge> AsTheCrowFlies::findEdges(const Vertex &v) const {
  
  
  Map map = mainGraph.getGraph();
  
  std::vector<Edge> edges;
  
  bool done = false;
  
  for (auto it = map.begin(); it!=map.end() && !done; ++it) {
    
    if(it->first==v) {
      
      edges=it->second;
      
      done = true;
      
    }
    
  }
  
  return edges;
  
  
}

