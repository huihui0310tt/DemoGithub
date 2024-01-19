# include <stdio.h>
# include <iostream>
# include <fstream>
// # include <sstream>
# include <string.h>
# include <stdlib.h>
# include <vector>

using namespace std ;

# define MODE 0
// MODE -> Loggin level   -> ALL(2) > DEBUG(1) > INFO(0)

class Vertex {

    string name ;
    int weight ;
    string io ;
    

    public:
    Vertex(string name, int weight, string io) {
        this->name = name ;
        this->weight = weight ;
        this->io = io ;
    } // Vertex()

    void show_info() {
        cout << "name is :" << name << endl ;
        cout << "weight is : " << weight << endl ;
        cout << "io is " << io << endl ;
        cout << endl ;
    } // show_info()


    string Get_IO() {
        return this->io ;
    } // Is_Output()

    string Get_Name() {
        return this->name ;
    } // GetName()

    int Get_Weight() {
        return this->weight ;
    } // Get_Weight()

} ; // Vertex

class Node {

    string name ;
    
    public:
    vector<Vertex> vertex_info ;


    Node(string name) {
        this->name = name ;
    } // Node()

    void show_info() {
        cout << "name is: " << name << endl; 
        cout << "vertex num : " << vertex_info.size() << endl ;
        for ( int i = 0 ; i < vertex_info.size() ; i++ ) {
            vertex_info[i].show_info() ;
        } // for
    } // show_info()

    void Add_vertex( Vertex subset_vertex ) {
        this->vertex_info.push_back(subset_vertex) ;
    } // Add_vertex()


    string GetName() {
        return this->name ; 
    } // GetName()


    bool HaveVectorInput( string name ) {
        for ( int i = 0 ; i < vertex_info.size() ; i++ ) {
            if ( vertex_info[i].Get_Name() == name && vertex_info[i].Get_IO() == "i" ) 
                return true ;
        } // for
        return false ;
    } // GetNode()


}; // Node()

class Read_Parse {

    public:
    bool Identify( char ch, bool space, bool enter, bool tab, bool comma, bool left_paren, bool right_paren) {
        // Identify(char, space, enter, tab, comma, left_paren, right_paren)
        // space = ' '
        // enter = '\n'
        // tab = '\t' 
        // 
    
        if ( ch == ' ' && space == true ) 
            return true ;
        if ( (ch == '\n' || ch == '\0' ) && enter == true )
            return true ;
        if ( ch == '\t' && tab == true ) 
            return true ;
        if ( ch == ',' && comma == true ) 
            return true ;
        if ( ch == '(' && left_paren == true ) 
            return true ;
        if ( ch == ')' && right_paren == true ) 
            return true ;
        return false ; 
    } // Identify()

    vector<string> ReadFile(string fileName) {  // data  file_loader
        vector<string> data_store ;
        char one_char ;
        vector<char> chars ;
        ifstream file_loader(fileName.c_str(), ios::in) ;
        // FILE * file_loader = fopen( fileName.c_str(), "r" );

        // if ( file_loader == NULL ) {
        if ( ! file_loader.is_open() ) {
            printf("File Load Error, Please check the input file Name \"input.txt!\"") ;
        } // if
        else {
            while( file_loader.get( one_char ) ) {
                chars.push_back(one_char) ;
            } // while
        } // else

        file_loader.close() ;

        string a = "" ;
        for ( int i = 0 ; i < chars.size() ; i++ ) {
            if ( (int)chars[i] == 13 ) {
                ;
            } // if
            else if ( chars[i] != '\n' ) {
                a = a + chars[i] ;
            } // else if
            else {
                data_store.push_back(a) ;
                a = "" ;
            }
        } // for

        // for ( int i = 0 ; i < chars.size() ; i++ ) {
        //     if (chars[i] == '\n')
        //         cout << "[Enter]" << endl ;
        //     else
        //         cout << chars[i] << " " << (int)chars[i] << endl ;
        // } // for

        return data_store ;
    } // ReadFile()

    vector<Node> Parser( vector<string> input ) {

        vector<Node> list ;
        int input_index = 0 ;
        string name = "" ;
   

        if ( input.size() == 0 ) 
            printf("Error!, input is 0") ;
            
        else if ( input[0] == "CIRCUIT avqlarge\0") {
        // else if ( strcmp(input[0].c_str(), "CIRCUIT avqlarge") == 0 ) {
            if ( MODE >= 2 ) 
                printf("pass title check\n") ;
    
            input.erase(input.begin()) ;
            while( input[0] !=  "ENDCIRCUIT\0" ) { 
                name = "" ;
                input_index = 0 ;
                while ( name != "INSTANCE" ) {
                    name = name + input[0][input_index] ;
                    input_index++ ;
                } // while

                name = "" ;// Identify(char, space, enter, tab, comma, left_paren, right_paren)
                while( Identify(input[0][input_index], true, false, true, false, false, false )) {
                    input_index++ ;
                } // while

                while( !Identify(input[0][input_index], true, false, true, false, false, false )) {
                    name = name + input[0][input_index] ;
                    input_index++ ;
                } // while

                Node temp_node(name) ;   // New Node
                input.erase(input.begin()) ;
                // cout << name << endl ;
                input_index = 0 ;

                do {
                    while( Identify(input[0][input_index], true, false, true, false, false, false )) {
                        input_index++ ;
                    } // while
                    name = "" ;
                    while( !Identify(input[0][input_index], false, false, false, false, true, false )) {
                        name = name + input[0][input_index] ;
                        input_index++ ;
                    } // while
                    string str_weight = "" ;
                    int int_weight = 0 ;
                    input_index++ ; // skip left_paren

                    while( Identify(input[0][input_index], true, false, true, false, false, false )) {
                        input_index++ ;
                    }  // while

                    while( !Identify(input[0][input_index], false, false, false, true, false, false )) {
                        str_weight = str_weight + input[0][input_index] ;
                        input_index++ ;
                    } // while

                    int_weight = atoi(str_weight.c_str()) ;
         
                    input_index++ ; // skip comma

                    while( Identify(input[0][input_index], true, false, true, false, false, false )) {
                        input_index++ ;
                    } // while
                    
                    string io = "" ;
                    if (input[0][input_index] == 'i' ) 
                        io = "i" ;
                    else 
                        io = "o" ;
                    

                    while( !Identify(input[0][input_index], false, false, false, false, false, true )) {
                        input_index++ ;
                    } // while

                    input_index++ ;

                    while( Identify(input[0][input_index], true, false, true, false, false, false )) {
                        input_index++ ;
                    } // while

                    if ( MODE >= 1 ) 
                        cout << name << "   " << int_weight << "    " << io << endl ;
    
                    temp_node.Add_vertex( Vertex(name, int_weight, io) ) ;
               
               
                      
                } while( !Identify(input[0][input_index], false, true, false, false, false, false )) ;

                input.erase(input.begin()) ;
                input_index = 0 ;


                list.push_back(temp_node) ;
            } // while

            return list ;
        } // else if
        else {
            printf("Error, Syntax Error!\n") ;
        } // else


    } // Parser()

    vector<Node> run() {

        return Parser(ReadFile("input.txt")) ;

    } // run()
} ; // Read_Parse

class DFS{
    vector<string> visited_node ;  // record the histroy of the visited Node 

    vector<string> stack_node ;


    
    bool Have_Visited(string name) {
        for ( int i = 0 ; i < visited_node.size() ; i++ ) {
            if ( visited_node[i] == name ) 
                return true ;
        }  // for

        return false ;
    } // Have_Visited()

    bool Have_Stack(string name) {
        for ( int i = 0 ; i < stack_node.size() ; i++ ) {
            if ( stack_node[i] == name ) 
                return true ;
        }  // for

        return false ;
    } // Have_Stack()

    string FindVectorOutput( string name, vector<Node> list ) {
        // input vector name 
        for ( int i = 0 ; i < list.size() ; i++ ) {
            if ( list[i].HaveVectorInput( name ) ) 
                return list[i].GetName() ;
        } // for
    } // FindVectorOutput()


    public:


    void run(vector<Node> list) {
        
        string now_node_name = "" ;
        vector<string> one_node_temp ;
        
        do  {
            one_node_temp.clear() ;


            // update the now_node_name 
            if ( now_node_name == "" ) 
                now_node_name = "S" ;
            else {
                now_node_name = stack_node.back() ;
                stack_node.pop_back() ;
            } // else


            // update visited_node ;
            visited_node.push_back( now_node_name ) ;



            // update the stack_node ;
            // watch out for the i/o
            // watch out for repeat node, let repeat node in the last ;
            // watch out for the visited node, do not let the node be stacked.
            // watch out for the unvisited & unrepeat node,  get the node name and compared them first, then pushed into the stack .

            for ( int i = 0 ; i < list.size() ; i++ ) {
                if ( list[i].GetName() == now_node_name ) {
                    for( int j = 0 ; j < list[i].vertex_info.size() ; j++ ) {
                        if ( list[i].vertex_info[j].Get_IO() == "i" ) {
                            ;
                        } // if
                        else {
                            string temp = FindVectorOutput(list[i].vertex_info[j].Get_Name(), list ) ;
                            if ( ! Have_Visited( temp ) ) {
                                if ( Have_Stack( temp ) ) {
                                    for ( int k = 0 ; k < stack_node.size() ; k++ ) {
                                        if ( stack_node[i] == temp ) 
                                            stack_node.erase(stack_node.begin()+k ) ;
                                            break ;
                                    } // for
                                } // if
                                one_node_temp.push_back( temp ) ;
                            } // if
                        } // else

                    } // for


                    for ( int j = 0 ; j < one_node_temp.size() ; j++ ) {
                        for ( int k = j+1 ; k < one_node_temp.size() ; k++ ) {
                            if ( one_node_temp[j] > one_node_temp[k] ) {
                                string temp_string = one_node_temp[k] ;
                                one_node_temp[k] = one_node_temp[j] ;
                                one_node_temp[j] = temp_string ;
                            } // if
                        } // for
                    } // for

                    while( one_node_temp.size() != 0 ) {
                        stack_node.push_back( one_node_temp.back() ) ;
                        one_node_temp.pop_back() ;
                    } // while

                    break ;
                } // if

            } // for


        } while ( stack_node.size() != 0 ) ;

        cout << "[DFS algorithm] (depth first search)" << endl ;
        cout << "Order: " ;
        for ( int i = 0 ; i < visited_node.size() ; i++ ) {
            if ( i == 0 )
                cout << visited_node[i] ;
            else {
                cout << " >> " << visited_node[i] ;
            } // else
            // cout << visited_node[i] << endl ;
        } // for

        cout << endl << endl ;
    } // run()



} ; // class DFS



class Dijkstra{
    int * table ;
    bool * visited ;

    int table_size ;

    vector<Node> list ;

    public:

    string FindVectorOutput( string name ) {
        // input vector name 
        for ( int i = 0 ; i < list.size() ; i++ ) {
            if ( list[i].HaveVectorInput( name ) ) 
                return list[i].GetName() ;
        } // for
    } // FindVectorOutput()

    bool All_Visited() {
        for ( int i = 0 ; i < table_size ; i++ ) {
            if ( visited[i] == false )
                return false ;
        } // for

        return true ;
    } // All_Visited() 

    int Find_List_Index( string name ) {

        // input Node's Name, then return the list's index 
        // if error, return -1
        for ( int i = 0 ; i < list.size() ; i++ ) {
            if ( list[i].GetName() == name ) 
                return i ;
        } // for

        return -1 ; 

    } // Find_List_Index()


    void run(vector<Node> list) {
        table = new int[list.size()] ;
        visited = new bool[list.size()] ;
        table_size = list.size() ;
        this->list = list ;

        // int table[list.size()] ;
        // bool visited[list.size()] ;

        string now_node_name = "" ;
        int now_node_weight ;
        int now_node_index = 0 ;

        for ( int i = 0 ; i < list.size() ; i++ ) {
            table[i] = -1 ;
            visited[i] = false ;
        } // for
        if ( MODE ) 
            cout << "[Difjstra] Table init successful!" << endl ;


        do {
            if ( now_node_name == "" ) {
                now_node_name = list[0].GetName() ;
                now_node_weight = 0 ;
                now_node_index = 0 ;
                table[0] = 0 ;
            } // if
            else {
                now_node_name = "" ;
                now_node_weight = 0 ;
                for ( int i = 0 ; i < list.size() ; i++ ) {
                    if ( ( table[i] != -1 ) && ( visited[i] == false ) ) {
                        if ( now_node_weight == 0 ) {
                            now_node_name = list[i].GetName() ;
                            now_node_weight = table[i] ;
                            now_node_index = i ;
                        } // if
                        else if ( table[i] < now_node_weight ) { 
                            now_node_name = list[i].GetName() ;
                            now_node_weight = table[i] ;
                            now_node_index = i ;
                        } // else if
                    } // if
                } // for
            } // else


            if ( now_node_weight == 0 && now_node_name != list[0].GetName() ) 
                break ;

            visited[now_node_index] = true ;


            for ( int i = 0 ; i < list[now_node_index].vertex_info.size() ; i++ ) {
                if ( list[now_node_index].vertex_info[i].Get_IO() == "o" ) {
                    int temp_index = Find_List_Index(FindVectorOutput(list[now_node_index].vertex_info[i].Get_Name())) ;
                    int temp_weight = now_node_weight + list[now_node_index].vertex_info[i].Get_Weight() ;
                    if ( table[temp_index] == -1 ) 
                        table[temp_index] = temp_weight ;
                    else if ( temp_weight < table[temp_index] ) 
                        table[temp_index] = temp_weight ;
                } // if
            } // for

            // update table

        } while( !All_Visited() ) ;

        for ( int i = 0 ; i < list.size() ; i++ ) {
            cout << "Vertex (" << list[i].GetName() << ") distance = " ;
            if ( table[i] == -1 ) 
                cout << "infinite" << endl ;
            else 
                cout << table[i] << endl ;
        } // for
    } // run()

} ; // class Dijkstra

int main() {
    int choice ;

    while( true ) {
        cout << "* * * * * * VLSI final project * * * * * *" << endl ;
        cout << "*          Student ID : 10727211         *" << endl ;
        cout << "* 0. QUIT                                *" << endl ;
        cout << "* 1. DFS (depth first search)            *" << endl ;
        cout << "* 2. shortest path(Dijkstra)             *" << endl ;
        cout << "******************************************" << endl ;
        cout << "Pleases input a choice(0, 1, 2): " ;
        cin >> choice ;

        if ( choice == 0 ) 
            break ;

        vector<Node> list ;
        Read_Parse parser ;
        list = parser.run() ;

        if ( MODE >= 2 ) {     // debug for print node info
            for ( int i = 0 ; i < list.size() ; i++ ) {
                list[i].show_info() ;
                cout << "-----" << endl ;
            } // for 
        } // if

        if ( choice == 1 ) {
            DFS dfs ; 
            dfs.run(list) ;            
        } // if
        else if ( choice == 2 ) {
            Dijkstra dijkstra ;
            dijkstra.run(list) ;            
        } // else if
        else {
            cout << "Choice Syntax Error, Please Try Again!" << endl ;
        }
        if ( MODE >= 0)
            cout << "End of the Simulate Successfully" << endl ;   

    } // while

    cout << "End System" << endl ;
} // main()