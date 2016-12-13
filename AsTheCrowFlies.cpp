


#include "AsTheCrowFlies.h"



AsTheCrowFlies::AsTheCrowFlies(){}

int AsTheCrowFlies::menu (char* filename) throw(std::exception) { //REVISED
    
    bool done = false;

    bool leave = false;

    main_city_list=processCityData(filename);	
    	  
    Graph new_graph(main_city_list);

    mainGraph.setGraph(new_graph.getGraph());


   do {

	cout << "As The Crow Flies" << endl;
    cout << std::endl;


    //The data field boolean variable 'done' and the do-while loop ensure
    //that the menu function continues to execute until the user exists the
    //program


    

        cout << "1. Load your cities from a file\n2. Display available cities\n3. Create a trip\n4. Add a city to available cities\n5. Find shortest between two cities\n6. Print text version of map of cities\n7. Exit program" << "Enter choice as integer [1-7]: "<<endl;

        //'i' represents the user's menu choice

        string choice;
        int i = 0;

        //The local boolean variable 'continueInput' ensures inner do-while
        //loop continues until the user has entered a valid menu choice

        bool continueInput = true;

        //Accepts menu choice from user and keeps prompting the user
        //to enter a choice if the entry is invalid

         while (continueInput) {
     
     	  	std::cout << "Enter a selection (1 through 7): " << std::endl;
     
     		getline(cin, choice);
     
     		if ((choice == "\n"||choice == "") && !leave) {
       
       			cout << "No value entered. Please enter a selection." << endl;
       			cin.clear();
       			choice.clear();
      			 if(!leave) {leave=true;}
       
       
     		} else if((choice == "\n"||choice == "") && leave) {
       
       		    cout<<"Would you like to exit this application? Enter 'y' if yes. " << endl;
      		    cin.clear();
       		    choice.clear();
                    getline(cin,choice);
       		    if(!(choice=="y"||choice=="Y")) {
         
         		continueInput=false;
        	        i=7;
         
       }
       
     }
     
     
     if(continueInput) {
       
       if (is_int(choice)) {

	 i = std::stoi(choice);         

         if(i <= 7 && i >= 1) {
           
           continueInput = false;
           
         } else {  
           
           std::cout << "Selection out of range! Please input a correct value." << endl;
           cin.clear();
           choice.clear(); 
           i = 0;  
           
         }  
         
         } else {
           
           std::cout << "Not a number! Please input a correct value." << endl;
           cin.clear();
           choice.clear();   
           i = 0;
           
         }
         
       }
       
     }
   //gets user menu input


  

	switch (i)
        {

        case 1:
        
	{
	    cout << "Enter a filename: " << endl;
            string filename;
            cin>>filename;
            user_city_list=processCityData(filename.c_str());
            break;

	}

	case 2:

	  if(main_city_list.size()<=0) {
            for (Vertex v : main_city_list)
            {

                std::cout << v.getName() <<", "<< v.getLatitude() << ", " << v.getLongitude() << std::endl;
            }
            cout << endl;
	   } else {cout<<"No cities to print"<<endl;}

            break;

	case 3:
            createTrip();
            break;

        case 4:
            addCity();
            break;

	case 5:

           minPathTrip = findShortestPath();  	    

           int total,curr;

	   if(minPathTrip.size()>0) {

	    std::cout<<"Minimum distance path is: "<<std::endl;

            for (int i = 0; i < minPathTrip.size()-1; i++)
            {
		curr=findMinDistance (minPathTrip[i].getLatitude(),minPathTrip[i].getLongitude(),
			minPathTrip[i+1].getLatitude(), minPathTrip[i+1].getLongitude())*31/50000;

                std::cout<< " From: " << minPathTrip[i].getName()  << " To: " << minPathTrip[i+1].getName() << " Dist:~  " << curr  <<" miles." << std::endl;

		total+=curr;
            }
            std::cout << std::endl;

	    std::cout<<"Total Distance for the Trip is: "<< total << " miles." << std::endl;

	    std::cout << std::endl;
	
	   } else {std::cout<<"No cities to print"<<endl;}

	    
	    break;

	
	case 6:

           mainGraph.printGraph();
           break;

	case 7:

            writeCitiesList("available_cities.txt");
            cout << "Thank you for your business.\nSaved " << "available cities to available_cities.txt" << endl;
            done = true;
            break;


	 default:

	     break;

        }


    

   } while(!done);

	 

   return 0; 

}



bool AsTheCrowFlies::is_int(const std::string& s)
{
    std::istringstream iss(s);
    int d;
    char c;
    return iss >> d && !(iss >> c);
}



bool AsTheCrowFlies::is_double(const std::string& s)
{
    std::istringstream iss(s);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}



std::vector<string> AsTheCrowFlies::split(const std::string &line, const char dlm) {
	
	vector<std::string> tokens;
	std::stringstream stream;
    	std::string item;
	stream.str(line);
	
	while(getline(stream, item, dlm)) {
    		tokens.push_back(item);
                
    	}
	
	return tokens;
  
}



 std::vector <Vertex> AsTheCrowFlies::processCityData (const std::string &filename) throw(std::exception) { //REVISED

    vector <Vertex> city_data;
    double latValue, longValue; // Holds validated latitude & longitude values //
    bool stop=false;

	
    string line;
    ifstream myStream;
	 
    myStream.open(filename.c_str());
	 
    if(!myStream.is_open()) {
	  cerr << "Couldn't open the text file. " << endl;

    }

    std::vector<std::vector<std::string>> raw_city_data;
	
    while (getline(myStream,line)) {
            
            vector<std::string> new_city_data=split(line,',');
	          raw_city_data.push_back(new_city_data);
            printf("1");
    }

    //The nested for loops below check each line entry to ensure
    //the data are the correct type and range and that it has each
    //required element
    
     for (auto it = raw_city_data.begin(); it != raw_city_data.begin(); ++it) {

	      std::vector<std::string> input = *it;	
              printf("2");

        if (input.size() != 3) {
          
           stop = true;
           printf("3");
      
        } else {
            
	          if(!(is_double(input[1]))||latValue < -90.0 || latValue > 90.0) {

	                   stop=true;		
		           break;
                           printf("4");
	  
            } else {latValue = std::stod(input[1]);}
            
	        if(!(is_double(input[3]))||longValue < -180.0 || longValue > 180.0) {

		          stop=true;
		          break;
                          printf("5");

            } else {longValue = std::stod(input[2]);printf("6");}

	  


    	if(!stop) {

	   Vertex newCity(input[0],latValue,longValue);
           printf("7");
	   
	   city_data.push_back(newCity);

           printf("8");
        }
 
      }

    	return city_data;
        printf("9");

	}

   } 




void AsTheCrowFlies::addCity() throw(std::exception) {
    
   bool stop = false;
   bool done = false;
   bool leave = false;
   std::string city, xString;
   double newLatitude, newLongitude;
   
   
   do {
   
   
   //Prompts user to enter city name. Will reprompt
   //if nothing entered
   
   while (!done && !stop) {
     
     std::cout << "Enter city name: " << std::endl;
     getline(cin, xString);
     if ((xString == "\n"||xString == "") && !leave) {
       
       cout << "No city name entered. Please enter a city name." << endl;
       cin.clear();
       xString.clear();
       leave=true;
       
       
     } else if((xString == "\n"||xString == "") && leave) {
       
       cout<<"Would you like to exit this application? Enter 'y' if yes. " << endl;
       
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
     
     std::cout << "Enter latitude as double (-90.0 to 90.0): " << std::endl;
     
     getline(cin, xString);
     
     if ((xString == "\n"||xString == "") && !leave) {
       
       cout << "No value entered. Please enter a latidue." << endl;
       cin.clear();
       xString.clear();
       leave=true;
       
       
     } else if((city == "\n"||city == "") && leave) {
       
       cout<<"Would you like to exit this application? Enter 'y' if yes. " << endl;
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
         
         if(newLatitude <= 90.0 && newLatitude >= -90.0) {
           
           done = true;
           
         } else {  
           
           std::cout << "Latitude out of range! Please input a correct value." << endl;
           cin.clear();
           xString.clear();   
           
         }  
         
         } else {
           
           std::cout << "Not a number! Please input a correct value." << endl;
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


     
     std::cout << "Enter longitude as double (-90.0 to 90.0): " << std::endl;
     
     getline(cin, xString);
     
     if ((xString == "\n"||xString == "") && !leave) {
       
       cout << "No value entered. Please enter a longitude." << endl;
       cin.clear();
       xString.clear();
       leave=true;
       
       
     } else if((city == "\n"||city == "") && leave) {
       
       cout<<"Would you like to exit this application? Enter 'y' if yes. " << endl;
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
         
         if(newLongitude <= 90.0 && newLongitude >= -90.0) {
           
           done = true;
           
         } else {  
           
           std::cout << "Longitude out of range! Please input a correct value." << endl;
           cin.clear();
           xString.clear();
           newLongitude = 0.0;   
           
         } 
         
         } else {
           
           std::cout << "Not a number! Please input a correct value." << endl;
           cin.clear();
           xString.clear();   
           newLongitude = 0.0;
           
         }
         
       }
     
     }
    
    

//Create new city object and enter data



if(done && !stop) {
  
    Vertex new_city(city,newLatitude,newLongitude);
    
    //Add new city to main list and update the graph

    main_city_list.push_back(new_city);
   
    mainGraph.insert(new_city);
 
    //Add new city to user's city list and print out new city data
  
    user_city_list.push_back(new_city);
    std::cout << "Added: " << new_city.getName() <<", "<< new_city.getLatitude() << ", " << new_city.getLongitude() << std::endl;
    std::cout << std::endl;

    //Ask user if they want to enter a new city. If not leave outermost do-while loop

    cout<<"Would you like to add another city? Enter 'y' if yes. " << endl;
    cin.clear();
    xString.clear();
    getline(cin,xString);
    stop=xString=="y"||xString=="Y"; 
     
    
    //Save user cities to standard file
    
    ofstream myStream("cities_added.txt");
    
    if (!myStream.is_open()) {
      cerr << "Couldn't open the file cities_added.txt" << endl;
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
            cerr << "Couldn't open the file" << endl;
		   }
		 // The commas act as delimitters//
		 for (Vertex v : main_city_list) {
		    std::string s = v.getName() + ", " + to_string(v.getLatitude()) + ", " + to_string(v.getLongitude());
		    out << s <<"\n";
         }

	    

    } catch (std::exception &FileNotFoundException) {
        std::cout << "Unable to read file\n" << std::endl;
        exit(1);
    }

	
}



void AsTheCrowFlies::createTrip() throw(std::exception) {
	

    bool done = false;
    bool end = false;
	
	do {

		vector<Vertex> cityList;


	cout << "There are " << main_city_list.size() << " cities to choose " << "from." << endl;
	

	if (tripList.size() > 0)
	{

		cout << "Add to current trip (y/n) ?" << endl;
	  
	  string choice;

		cin >> choice ;
		if (choice=="n"||choice=="N") {
			
			tripList.clear();
			cout << "There are " << main_city_list.size() << " cities to choose " << "from." << endl;
			cout << "New trip created, needs at least two cities" << endl;
		}
	}

	//The while loop controls user entry and new city count

	bool cityEntered = true;
	int validCitiesEntered = 0;

	while (cityEntered)
	{

		cout << "Enter next city name (or enter to end) : " << endl;
		std::string temp;
		getline(cin,temp);

		if(temp=="\n"||temp=="") {

		  cout<<"You did not enter a city name. Are you sure you want to quit? If so, enter 'Y' or 'y', otherwise enter a city name "<<endl;
                  cin.clear();
	          temp.clear();
		  getline(cin,temp);
	
		  if(temp=="y"||temp=="Y") {

			cityEntered = false;
			break;
		
			}

		} else {
			
                    for (int i = 0; i < main_city_list.size(); i++) {
				
                           if (main_city_list[i].getName()==temp) {
					++validCitiesEntered;
					cityList.push_back(main_city_list[i]);
				}
			    }
		        }
	             }

	//The if loop ensures there two or more valid cities entered above
	//before the string of cities is split and loaded into the string array
	 

	if (validCitiesEntered > 1)
	{

		Vertex start, stop;

		cout << "There are " << validCitiesEntered << " cities in" << " this trip." << endl;



		for (int i =0; i < cityList.size()-1; i++) {

			double dist;
		
			dist = findMinDistance(cityList[i].getLatitude(),cityList[i].getLongitude(),cityList[i+1].getLatitude(),cityList[i+1].getLongitude());

		        Edge edge(cityList[i],cityList[i+1],dist);					  			
			   
			tripList.push_back(edge);

		}

			int totalDist = 0;


			for (int k = 0; k < tripList.size(); k++) {
				
                                start = tripList[k].getOrigin();

				stop = tripList[k].getDestination();
			
				cout << "From: " << start.getName() << "To: " << stop.getName() << "Miles: " << ( tripList[k].getDistance() ) * 31 / 50000 <<endl;

				totalDist += tripList[k].getDistance();
			}

			cout << "Total Distance: " << totalDist << " meters (~" << totalDist * 31 / 50000 << " miles)" << endl;

			cout << "Write trip details to file [y/n} ? " << endl;
			string save; 
	      	        getline(cin, save);

			done=!(save=="y"||save == "Y");

			if(done) {end=done;} //ensures do-while terminated so function terminates as well
		
		while(!done) {
		
			string tripFileName;

			cout << "Enter filename: " << endl;
			
			getline(cin, tripFileName);

			if (tripFileName=="\n"||tripFileName=="") {

			  cout<<"That was a not a valid file name. Please try again. If you want to try again, please select 'y' or 'Y' "<<endl;
				
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
			       cerr << "Couldn't write to the file" << endl;
	 			} 

			    for(int k = 0; k < tripList.size(); k++) {
				
					start=tripList[k].getOrigin();
					stop=tripList[k].getDestination();
					out << start.getName() << ", "<< stop.getName() <<", "<<tripList[k].getDistance() << "\n";
			
				}

			  done=end=true;

			}

			}
	 

	 
	 }


	else {
		cout << "Must have at least 2 cities in a trip. Did you want to continue? If not, please select 'n' or 'N' " << "" << endl;
		
		string str;

		cin>>str;

		end=str=="n"||str=="N";

	        cout<<endl;
		
	    } 
	
	} while(!end);


   return;


} 

std::deque <Vertex> AsTheCrowFlies::findShortestPath() { //NEW

	std::deque <Vertex> path; //return value; may be empty
	
	bool stop = false; //causes function to end if user indicates
	
	bool done = false; //ends entry loop
	
	std::string temp; //temporary string value for city name
	 
	Vertex origin, target; //start Vertex and stop Vertex respectively


//Prompt user to enter starting city

	while(!done && !stop) {

		cout << "Enter starting city name (or enter to end) : " << endl;
		
		getline(cin,temp);

		//If the user does not enter anything check to see if they want to quit...
		//...and set done and stop to true if the user requests it

		if(temp=="\n"||temp=="") {

		  cout<<"You did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y' "<<endl;

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
					
				}
			}

			if (!done) { //...reprompt user if no matching city name and give them the option of exiting the function again
			
				std::cout<<"There was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
				
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

		cout << "Enter destination city name: " << endl;
		
		getline(cin,temp);

		if(temp=="\n"||temp=="") {

		  std::cout<<"You did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y' "<<std::endl;

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
					
				}
			  }

                       

			if (!done) { //...reprompt user if no matching city name and give them the option of exiting the function again

			
				std::cout<<"There was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
				
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
 
     //Data structures for while loop below	
      
      set<PQI,PQI_Comp> priority_queue; //priority queue for iteration in while loop
      unordered_map<Vertex,double,VertexHash,VertexEqual> dist_map; //stores current min distance to each Vertex
      unordered_map<Vertex,Vertex,VertexHash,VertexEqual> path_mapping;	//stores ordered listing of Vertices visited
      	
      //Initial values for min dist map are set to INFINITY

      for(auto it = main_city_list.begin(); it!=main_city_list.end(); ++it) {
        
	  dist_map[*it] = INFINITY;	        

	  }

     PQI start_node = make_pair(0.0, origin); //first node in priority queue

     priority_queue.insert(start_node); //Start vertex has distance of zero and is added to PQ

     Vertex stop_node ("", 0.0, 0.0); //used indicte where to stop when adding nodes to final path

     Vertex prev = stop_node;

     Vertex curr = origin;

     dist_map[curr]=0.0; //distance from origin to itself is zero

     path_mapping[curr]=prev; //sets stopping point for path map when final list is made

     while(!priority_queue.empty()) {

	prev=curr; //make current value previous value now

        curr=priority_queue.begin()->second; //reset curr to Vertex of highest priority pair

        if(curr==target) { //If the target node is reached...


           while(curr!=stop_node) {//...set add each previous node to the front start...
			      //...starting with current node and then get prior node...
			     //...and continue until initial stop_node reached

		path.push_front(curr);
 
		curr = path_mapping[curr];    
		
		}

	  return path; //return path deque which has origin as start and target as end

        } else {

		  if(curr!=origin) {
		    path_mapping[curr]=prev;
		    
                   } //updates path_map with most current pair of the previous and current nodes
		    

		  priority_queue.erase(priority_queue.begin()); //"pop" PQ
		  

		  for (Edge edge : findEdges(curr)) { //Get edges to from current Vertex


			//if distance to new edge is greater than current distance...
			//...plus distance from prior edge than update that Vertex
                        // ...on the map and replace on PQ
                    
			
			if(dist_map[edge.getDestination()]>dist_map[curr]+edge.getDistance()) {
			  
			  	PQI subtract = make_pair(dist_map[edge.getDestination()],edge.getDestination());

				priority_queue.erase(subtract);

				dist_map[edge.getDestination()]=dist_map[curr]+edge.getDistance();
			  
			 	PQI add = make_pair(dist_map[edge.getDestination()],edge.getDestination());

				priority_queue.insert(add);

			}

		      }
		  
        
		     
		    }

			

       	         }

        return path; //will return empty path if target node not reached       
      
   
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


