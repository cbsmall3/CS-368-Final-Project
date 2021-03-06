#include "AsTheCrowFlies.h"
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

std::vector<Vertex> AsTheCrowFlies::main_city_list;
std::vector<Vertex> AsTheCrowFlies::user_city_list;
std::vector<Edge> AsTheCrowFlies::tripList;


vector<string> AsTheCrowFlies::split(string str, const char dlm) {
  
  vector<std::string> tokens;
  
  stringstream stream;
  
  string item;
  
  stream.str(str);
  
  while(getline(stream,item,dlm)) {
  
    tokens.push_back(item);
    
  }

 return tokens;
  
}

double getDistance(double latStart, double longStart, double latEnd, double longEnd) { //REVISED
	double x, y, z, a;
	
	//const double pi = 2 * std::acos(0.0);
	latEnd = PI * latEnd/180;
	latStart = PI * latStart/180;
	longEnd = PI * longEnd/180;
	longStart = PI * longStart/180;
	y = std::pow(std::sin((latEnd - latStart) / 2), 2);
	z = std::pow(std::sin((longEnd - longStart) / 2), 2);
	x = y + std::cos(latEnd) * std::cos(latStart) * z;
	a = std::atan2(std::sqrt(x), std::sqrt(1 - x));
	return 2 * EARTH_RADIUS * a;
}




void AsTheCrowFlies::processCityList(const string &filename) {

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
    }

    //The nested for loops below check each line entry to ensure
    //the data are the correct type and range and that it has each
    //required element
    
     for (auto it = raw_city_data.begin(); it != raw_city_data.end(); ++it ) {

	std::vector<std::string> input = *it;
	stop=false;	

        if (input.size() != 3) {
	    stop=true;
	    break;
        } else {
            
	    if(!(latValue << input[1])||latValue < -90.0 || latValue > 90.0) {
	
		stop=true;
		break;
	  
            } else {latValue = std::stod(input[1]);}
            
	    if(!(longValue << input[3])||longValue < -180.0 || longValue > 180.0) {

		stop=true;
		break;

            } else {longValue = std::stod(input[2]);}

	  


    	if(!stop) {

	   Vertex newCity (input[0],latValue,longValue);

	   city_data.push_back(newCity);
        }
 
      }

     }

    	return city_data;
}

void AsTheCrowFlies::writeCitiesList(const std::string &filename)
{

     try {
        ofstream out;
        out.open(filename.c_str());
        if(!out.is_open()) {
            cerr << "Couldn't open the file" << endl;
		 }
		 // The commas act as delimitters//
		 for (Vertex v : main_city_list) {
		    out << v->city_name <<","<< v->latitude << "," << v->longitude<<"\n";
         }

	return;

    } catch (std::exception &FileNotFoundException) {
        std::cout << "Unable to read file\n" << std::endl;
        exit(1);
    }

}


void AsTheCrowFlies::createTrip() throw(std::exception)
{

	bool stop=false;
	
	do {

		vector<Vertex> cityList;


	cout << "There are " << main_city_list.size() << " cities to choose " << "from." << endl;
	

	if (tripList.size() > 0)
	{

		cout << "Add to current trip (y/n) ?" << endl;

		string choice << cin;
		if (choice=="n"||choice=="N")
		{
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

			cin.clear()
	                temp.clear()
			
			getline(cin,temp);
	
			if(temp="y"||temp="Y") {

			cityEntered = false;
			break;
		
			}

		}
		else
		{
			for (int i = 0; i < main_city_list.size(); i++)
			{
				if (main_city_list[i]->city_name==temp)
				{
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

			start = cityList[i];
					
                        stop = cityList[i+1];

			double dist = getDistance(start->latitude,start->longitude,stop->latitude,stop->longitude);

		        Edge edge (start, stop, dist);
					
			tripList.push_back(edge);

		}

			int totalDist = 0;


			for (int k = 0; k < tripList.size(); k++)
			
			{
				start = tripList[k]->orig;

				stop = tripList[k]->dest;
			
				cout << "From: " << stop->city_name << "To: " << stop->city_name << "Miles: " << ( tripList[k]->dist ) * 31 / 50000 <<endl;

				totalDist += tripList[k]->dist;
			}

			cout << "Total Distance: " << totalDist << " meters (~" << totalDist * 31 / 50000 << " miles)" << endl;

			cout << "Write trip details to file [y/n} ? " << endl;
			string save; 
	      	        getline(cin, save);

			if (save=="y"||save == "Y")
			{

			bool done=false

			}
		
			string tripFileName;

		do {
		
			cout << "Enter filename: " << endl;
			getline(cin, tripFileName);

			if (tripFileName=="\n"||tripFileName=="") {

			  cout<<"That was a not a valid file name. Please try again. If you want to try again, please select 'y' or 'Y' "<<endl;
				
   			  cin.clear();
			
			  tripFileName.clear();                      

			  getline(cin, tripFileName);

  			  if(tripFileName="y"||tripFileName=="Y") {

				done=true;

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

			    for(int i = 0; i < tripList.size(); i++) {
				
					start=tripList[k]->orig;
					stop=tripList[k]->dest;
					out << start->city_name << ", "<< stop->city_name <<", "<<tripList[i]->dist << "\n";
			
				}

			  done=true;

			}

			} while(!done)
	 
	     	  stop=true;
	 
	 }
	else
	{
		cout << "Must have at least 2 cities in a trip. Did you want to continue? If not, please select 'n' or 'N' " << "" << endl;
		
		string str;

		str<<cin;

		if(str=="n"||str=="N") {

			stop=true;

		}

	  cout<<endl;
		} 
	} while(!stop)


   return;

}

std::deque <Vertex> findShortestTrip() { //NEW

	deque <Vertex> path; //return value; may be empty
	
	bool stop = false; //causes function to end if user indicates
	
	bool done = false; //ends entry loop
	
	std::string temp; //temporary string value for city name
	 
	Vertex origin, target; //start Vertex and stop Vertex respectively


//Prompt user to enter starting city

	do {

		cout << "Enter starting city name (or enter to end) : " << endl;
		
		getline(cin,temp);

		//If the user does not enter anything check to see if they want to quit...
		//...and set done and stop to true if the user requests it

		if(temp=="\n"||temp=="") {

		  cout<<"You did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y', otherwise enter a city name "<<endl;

			cin.clear()
	                temp.clear()
			
			getline(cin,temp);
	
			if(temp="y"||temp="Y") {

			done = true;
			stop = true;
			break;
		
			}

			//For valid entries, see if it matches a city on the main list...

			for (int i = 0; i < main_city_list.size() && !done; i++)
			
			{
				if (main_city_list[i]->city_name==temp) //..if it does set origin to this city else...
				{

					done = true;
					origin=main_city_list[i];
					
				}
			}

			if (!done && !stop) { //...prompt user and give them the option of exiting the function again
			
				std::cout<<"There was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
				
				cin.clear()
	                	temp.clear()
			
				getline(cin,temp);

				if(temp="n"||temp="N") {

				    done = true;
				    stop = true;
				    break;
		
				}
			}
	
	} while(!done && !stop)

	if(stop) //If user indicated that they want to terminate input return empty path
	  return path;

        //reset values for destination city and repeat same process as above
	done = false;
	temp.clear();
	cin.clear();

	do {

		cout << "Enter destination city name: " << endl;
		
		getline(cin,temp);

		if(temp=="\n"||temp=="") {

		  std::cout<<"You did not enter a city name. Do you want to quit? If so, enter 'Y' or 'y', otherwise enter a city name "<<std::endl;

			cin.clear()
	                temp.clear()
			
			getline(cin,temp);
	
			if(temp="y"||temp="Y") {

			done = true;
			stop = true;
		
			}
  
                    }

			for (int i = 0; i < main_city_list.size() && !done; i++)
			{
				if (main_city_list[i]->city_name==temp)
				{

					done = true;
					target=main_city_list[i];
					
				}
			}

			if (!done && !stop) {
			
				std::cout<<"There was no matching city on the list. Would you like to try again? If not, enter 'n'"<<std::endl;
				
				cin.clear()
	                	temp.clear()
			
				getline(cin,temp);

				if(temp="n"||temp="N") {

				    done = true;
				    stop = true;
		
				}

			     }
		
	
	} while(!done && !stop)



      if (stop)
	return path;

      set <pair<double,Vertex>>currVertices; //Acts a priority queue (PQ) with double as sort index
      
      unordered_map<Vertex, double> dist; //holds current shortest distance to this Vertex
      
      unordered_map<Vertex, Vertex> path_map; //Each Vertex key's value indicates Vertex previous visited
      
      Vertex prev,curr; //placeholder Vertex variables

      //Initial values for min dist map are set to double max value

      for(auto it = main_city_list.begin(); it!=main_city_list.end(); ++it) {

		dist[*it]=DBL_MAX;
	
	}

     currVertices.insert({0.0,origin}); //Start vertex has distance of zero and is added to PQ

     curr=NULL; //set current point to NULL

     path_map[origin]=curr; //origin value in path map set to NULL to label start pt

     while(!currVertices.empty()) {

	prev=curr; //make current value previous value now

        curr=currVertices.begin()->second; //reset curr to Vertex of highest priority pair

        if(curr==target) { //If the target node is reached...


           while(curr!=NULL) {//...set add each previous node to the front start...
			      //...starting with current node and then get prior node...
			     //...and continue until initial NULL reached

		path.push_front(curr);
		curr = path_map[curr];


          }

	  return path; //return path deque which has origin as start and target as end

        } else {

		  if(curr!=origin)
		    path_map[curr]=prev; //set new map entry for prior leg of trip

		  currVertices.erase(currVertices.begin()); //"pop" PQ

		  for (Edge edge : mainGraph[curr]) {


			//if distance to new edge is greater than current distance...
			//...plus distance from prior edge than update that Vertex
                        // ...on the map and replace on PQ
			
			if(dist[edge->dest]>dist[curr]+edge->dist) {

				currVertices.erase({dist[edge->dest],edge->dest});

				dist[edge->dest]=dist[curr]+edge->dist;

				currVertices.insert({dist[edge->dest],edge->dest});

			}

		      }
		     
		    }

       	         }

        return path; //will return empty path if target node not reached       
      
   
	}


int main(int argc, char *argv[]) throw(std::exception) { //REVISED
    // Check if the program is given 2 command line arguments
    // including the program name.
    if (argc !=2 )) {
        std::cerr << "USAGE: ./a.out <total_city_list>"
                  << std::endl;
        return -1;
    }

    // Open the input file(s) containing the raw data.

    bool done = false;

    main_city_list=processCityData(argv[1]);
    
    Graph mainGraph (main_city_list);


   do {

	/*cout << "As The Crow Flies" << endl;
    cout << std::endl;


    //The data field boolean variable 'done' and the do-while loop ensure
    //that the menu function continues to execute until the user exists the
    //program


    do
    {

        cout << "1. Load your cities from a file\n2. Display available cities\n3. Create a trip\n4. Add a city to available cities\n5. Find shortest between two cities\n6. Exit program" << "Enter choice as integer [1-6]: "<<endl;

        //'i' represents the user's menu choice

        int i = 0;

        //The local boolean variable 'continueInput' ensures inner do-while
        //loop continues until the user has entered a valid menu choice

        bool continueInput = true;

        //Accepts menu choice from user and keeps prompting the user
        //to enter a choice if the entry is invalid

        do
        {
            try
            {

                i << cin;

                if (i < 1 || i > 6)
                {
                    cout << "Input out of range. Try again." << endl;
                    i<<cin;
                }
                else
                {
                    continueInput = false;
                }

            }
            catch (InputMismatchException ex)
            {
                cout << "Invalid input. Try again." << endl;
                cin.clear();
                cin>>i;
            }
        } while (continueInput); //gets user menu input


	switch (i)
        {

        case 1:
        
	{
	    cout << "Enter a filename: " << endl;
            string filename;
            cin>>filename;
            user_city_list=processCityList(filename.c_str());
            break;

	}

	case 2:

	  if(main_city_list.size()<=0) {
            for (Vertex v : main_city_list)
            {

                std::cout << v->city_name <<", "<< v->latitude << ", " << v->longitude << std::endl;
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
	    
           deque <Vertex> minPathTrip = findShortestTrip();

           int total,curr;

           std::cout<<"Minimum distance path is: "<<std::endl;

	   if(minPathTrip.size()<=0) {
            for (int i = 0; i < minPathTrip-1; i++)
            {
		curr=getDistance (minPathTrip[i]->latitude,minPathTrip[i]->longitude,
			minPathTrip[i+1]->latitude, minPathTrip[i+1]->longitude)*31/50000

                std::cout<< " From: << minPathTrip[i]->city_name  << " To: " << minPathTrip[i+1]->city_name << " Dist:~  " << curr  <<" miles." << std::endl;

		total+=curr;
            }
            std::cout << std::endl;

	    std::cout<<"Total Distance for the Trip is: "<< total << " miles." << std::endl;

	    std::cout << std::endl;
	
	   } else {std::cout<<"No cities to print"<<endl;}

	    
	    break;

        case 6:
            
	    writeCitiesList("available_cities.txt");
            cout << "Thank you for your business.\nSaved " << "available cities to available_cities.txt" << endl;
            done = true;
            break;

        default:

        }




   } while(!done)


   return 0;

}
