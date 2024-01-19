# include <stdio.h>
# include <string>
# include <vector>
# include <iostream>

# define MODE 0

using namespace std ;

// END_OF_LINE
enum NodeType { INTERNAL_NODE, SEMI, DOT, SINGLE_QUOTE, DOUBLE_QUOTE, SYMBOL, INT, FLOAT, STRING, NIL, T, 
              LEFT_PAREN, RIGHT_PAREN, NONE 
} ; 


int Char_To_Int( char ch ) {
  if ( ch == '0' )        return 0 ;
  else if ( ch == '1' )    return 1 ;
  else if ( ch == '2' )    return 2 ;
  else if ( ch == '3' )    return 3 ;
  else if ( ch == '4' )    return 4 ;
  else if ( ch == '5' )    return 5 ;
  else if ( ch == '6' )    return 6 ;
  else if ( ch == '7' )    return 7 ;
  else if ( ch == '8' )    return 8 ;
  else if ( ch == '9' )    return 9 ;
  return 999 ;
} // Char_To_Int()

float String_To_Float( string str ) {
  // 不管精準度ff

  bool neg = false ;
  float base = 0.1 ;
  float total = 0 ;
  
  if ( str.at( 0 ) == '-' ) {
    neg = true ;
    str.erase( str.begin() ) ;
  } // if
  else if ( str.at( 0 ) == '+' ) {
    neg = false ;
    str.erase( str.begin() ) ;
  } // else if 
  
  for ( int i = 0 ; str.at( i ) != '.' ; i++ ) {
    base = base * 10 ;
  } // for

  while ( ! str.empty() ) {
    if ( str.at( 0 ) == '.' ) 
      ;
    else {
      total = total + Char_To_Int( str.at( 0 ) ) * base ;
      base = base / 10 ;      
    } // else 

    str.erase( str.begin() ) ;
  } // while

  if ( neg )
    total = total * -1 ;
  return total ;
} // String_To_Float()

string Deal_Plus( string str ) {
  if ( str[0] == '+' )  
    str.erase( str.begin() ) ;

  return str ;
} // Deal_Plus()



class KeyDefine {
  
  NodeType m_type ; 
  string m_key ;
  int m_line ;
  int m_column ;  

  public :
  KeyDefine() { } // constructor()    

  KeyDefine( NodeType setType, string setKey, int setLine, int setColumn ) {    // constructor()
    m_type = setType ;
    if ( m_type == NIL ) 
      m_key = "nil" ;
    else if ( m_type == T )
      m_key = "#t" ;
    else if ( m_type == INT ) 
      m_key = Deal_Plus( setKey ) ;
    else if ( m_type == FLOAT ) 
      m_key = Deal_Plus( setKey ) ;
    else
      m_key = setKey ;
    m_line = setLine ;
    m_column = setColumn ;
  } // KeyDefine()   constructor() 

  NodeType GetType() {
    return m_type ;
  } // GetType()

  string GetKey() {
    return m_key ;
  } // GetKey()

  void SetType( NodeType type ) {
    m_type = type ;
  } // SetType()

  void SetKey( string key ) {
    m_key = key ;
  } // SetKey() 

  void PrintType( bool end_line ) {
    if ( m_type == INTERNAL_NODE )        cout << "INTERNAL_NODE" ;
    else if ( m_type == SEMI )            cout << "SEMI" ;
    else if ( m_type == DOT )             cout << "DOT" ;
    else if ( m_type == SINGLE_QUOTE )    cout << "SINGLE_QUOTE" ;
    else if ( m_type == DOUBLE_QUOTE )    cout << "DOUBLE_QUOTE" ;
    else if ( m_type == SYMBOL )          cout << "SYMBOL" ;
    else if ( m_type == INT )             cout << "INT" ;
    else if ( m_type == FLOAT )           cout << "FLOAT" ;
    else if ( m_type == STRING )          cout << "STRING" ;
    else if ( m_type == NIL )             cout << "NIL" ;
    else if ( m_type == T )               cout << "T" ;
    else if ( m_type == LEFT_PAREN )      cout << "LEFT_PAREN" ;
    else if ( m_type == RIGHT_PAREN )     cout << "RIGHT_PAREN" ;
    else cout << "UnKnown Type in PrintType()" ;

    if ( end_line ) 
      cout << endl ;
  } // PrintType()

  void PrintKey( bool end_line ) {
    if ( m_type == INTERNAL_NODE )        cout << "(key)INTERNAL_NODE" ;
    else if ( m_type == SEMI )            cout << "(key)SEMI" ;
    else if ( m_type == DOT )             cout << m_key ;
    else if ( m_type == SINGLE_QUOTE )    cout << "quote" ;
    else if ( m_type == DOUBLE_QUOTE )    cout << m_key ;
    else if ( m_type == SYMBOL )          cout << m_key ;
    else if ( m_type == INT )             cout << m_key ;
    else if ( m_type == FLOAT )           printf( "%.3f", String_To_Float( m_key ) ) ;
    else if ( m_type == STRING )          cout << m_key ;
    else if ( m_type == NIL )             cout << "nil" ;
    else if ( m_type == T )               cout << "#t" ;
    else if ( m_type == LEFT_PAREN )      cout << "(" ;
    else if ( m_type == RIGHT_PAREN )     cout << ")" ;
    else cout << "UnKnown Type in PrintType()\n\n\n" ;

    if ( end_line ) 
      cout << endl ;
  } // PrintKey()

  int GetLine() {
    return m_line ;
  } // GetLine()

  int GetColumn() {
    return m_column ;
  } // GetColumn()

};

class Tree {
  public : 
  KeyDefine m_key ;
  Tree * m_left ;
  Tree * m_right ;

  Tree() {
    m_left = NULL ;
    m_right = NULL ;
  } // Tree() 
};

int gTestNum ;      // PAL special format
int gLine = 0 ;     // present the vector location    (start from 0 ...)
int gColumn = 0 ;   // present the vector location    (start from 0 ...)
char gGetChar = '\0' ;

Tree * g_Tree ;
Tree * g_Result ;

KeyDefine gToken ;  // remind to give none value 
vector<KeyDefine> gDealToken ;
vector<Tree *> g_Define_Binding ;





class Read_Exp {

  char Int_To_Char( int i ) {
    if ( i == 0 )          return '0' ;
    else if ( i == 1 )     return '1' ;
    else if ( i == 2 )     return '2' ;
    else if ( i == 3 )     return '3' ;
    else if ( i == 4 )    return '4' ;
    else if ( i == 5 )    return '5' ;
    else if ( i == 6 )    return '6' ;
    else if ( i == 7 )    return '7' ;
    else if ( i == 8 )    return '8' ;
    else if ( i == 9 )    return '9' ;
    return '0' ;
  } // Int_To_Char()

  string Int_To_String( int i ) {
    string s ;
    while ( i / 10 != 0 ) {
      s = Int_To_Char( i % 10 ) + s;
      i = i / 10 ;
    } // while

    s = Int_To_Char( i % 10 ) + s;
    return s ;
  } // Int_To_String() 

  bool IsDigit( char ch ) {
    if ( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
          ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ) 
      return true ;
    else 
      return false ;
  } // IsDigit() 

  bool IsWhiteSpace( string str ) {
    if ( str == "\n" || str == "\t" || str == " " ) 
      return true ;
    else                                              
      return false ;
  } // IsWhiteSpace()

  bool IsSpace( string str ) {
    if ( str == " " )        
      return true ;
    else                     
      return false ;
  } // IsSpace()

  bool IsTab( string str ) {
    if ( str == "\t" )                             
      return true ;
    else                                            
      return false ;
  } // IsTab()

  bool IsEnter( string str ) {
    if ( str == "\n" )                      
      return true ;
    else                                            
      return false ;
  } // IsEnter()

  bool IsINT( string str ) {
    bool have_digit = false ;
    for ( int i = 0 ; i < str.length() ; i++ ) {
      if ( IsDigit( str[i] ) ) 
        have_digit = true ;

      if ( i == 0 ) {
        char ch = str[0] ;
        if ( ch != '+' && ch != '-' && !IsDigit( ch ) )
          return false ;
      } // if
      else {
        if ( ! IsDigit( str[i] ) ) 
          return false ;
      } // else
    } // for
    
    if ( have_digit )
      return true ;

    return false ;
  } // IsINT()

  bool IsFLOAT( string str ) {
    int count_dot = 0 ;
    string tostring ;
    bool have_digit = false ;
    for ( int i = 0 ; i < str.length() ; i++ ) {
      tostring = str[i] ;  
      if ( IsDigit( str[i] ) ) 
        have_digit = true ;
      if ( i == 0 ) {
        char ch = str[0] ;
        if ( ch != '+' && ch != '-' && tostring != "." && !IsDigit( ch ) )
          return false ;
        else {
          if ( tostring == "." ) 
            count_dot++ ;
        } // else 
      } // if
      else {
        if ( tostring == "." ) 
          count_dot++ ;
        else if ( ! IsDigit( str[i] ) ) 
          return false ;
      } // else
    } // for

    if ( count_dot == 1 && have_digit )
      return true ;
    else 
      return false ;
  } // IsFLOAT()

  bool IsDoubleQUOTE( string str ) {
    if ( str == "\"" )      return true ;
    else                    return false ;
  } // IsDoubleQUOTE()

  bool IsBackSlash( string str ) {
    if ( str == "\\" )      return true ;
    else                    return false ;
  } // IsBackSlash() 

  bool IsSYMBOL( string str ) {
  /**
   * Before call this function, should check int() float() quote()
  */
    string tostring ;
    for ( int i = 0 ; i < str.length() ; i++ ) {
      tostring = str[i] ;
      if ( str[i] == '(' || str[i] == ')' || str[i] == '\'' || str[i] == '\"' || IsWhiteSpace( tostring ) ) 
        return false ;
    } // for

    return true ;
  } // IsSYMBOL()

  NodeType GetType( string str ) {
    if ( str.at( 0 ) == ';' )            
      return SEMI ;
    else if ( str == "(" )     
      return LEFT_PAREN ;
    else if ( str == ")" )
      return RIGHT_PAREN ;
    else if ( str == "." )
      return DOT ;
    else if ( str == "t" || str == "#t" )
      return T ;
    else if ( str == "nil" || str == "#f" )
      return NIL ;
    else if ( str == "\'" )     
      return SINGLE_QUOTE ;
    else if ( IsINT( str ) )     
      return INT ;
    else if ( IsFLOAT( str ) )         
      return FLOAT ;
    else if ( IsSYMBOL( str ) )       
      return SYMBOL ;
    else                                
      return STRING ;
  } // GetType()

  KeyDefine GetToken() { 

    string getString = "" ;
    string chartoString ; 
    bool round_one = false ;

    bool exception_escape = false ;
    bool exception_string = false ;
    bool exception_semi = false ;
    int store_line = 0 ;
    int store_column = 0 ;

    if ( gLine == 0 ) {
      gLine = 1 ;
      round_one = true ;
    } // if

    bool bool_true = true ;   // while ( true )

    while ( bool_true ) {

      if ( gGetChar != '\0' ) 
        ;
      else if ( scanf( "%c", &gGetChar ) == EOF ) {
        throw 1 ;
      } // else if 

    
      chartoString = gGetChar ;
      
      if ( exception_semi ) {    
        // getString = getString + chartoString ;
        gGetChar = '\0' ;
        if ( chartoString == "\n" ) {
          if ( round_one ) {
            gLine = 1 ;
            round_one = false ; 
          } // if
          else
            gLine++ ;
          gColumn = 1 ;
          exception_semi = false  ;
          round_one = false ;
        } // if
        else {
          gColumn++ ;
        } // else     
      } // if
      else if ( exception_string ) {
        
        if ( chartoString == "\n" ) {
          cout << "ERROR (no closing quote) : END-OF-LINE encountered at Line " 
          + Int_To_String( gLine ) + " Column " + Int_To_String( gColumn ) << endl ;

          throw 2 ;
        } // if

        gGetChar = '\0' ;
        
        gColumn++ ;

        if ( exception_escape ) {
          if ( chartoString == "\"" ) 
            getString = getString + "\"" ;
          else if ( chartoString == "t" ) 
            getString = getString + "\t" ;
          else if ( chartoString == "n" ) 
            getString = getString + "\n" ;
          else if ( chartoString == "\\" ) 
            getString = getString + "\\" ;
          else 
            getString = getString + "\\" + chartoString ;

          exception_escape = false ; 
        } // if
        else if ( IsDoubleQUOTE( chartoString ) ) {
          getString = getString + "\"" ;
          bool_true = false ;
        } // else if
        else if ( IsBackSlash( chartoString ) ) {
          exception_escape = true ;
        } // else if 
        else 
          getString = getString + chartoString ;
      } // else if
      else if ( IsWhiteSpace( chartoString ) ) {

        if ( getString != "" )  
          bool_true = false ;
        else if ( chartoString == "\n" ) {
          gGetChar = '\0' ;
          if ( round_one ) {
            gLine = 1 ;
            round_one = false ;
          } // if
          else
            gLine++ ;
          gColumn = 1 ;
        } // else if
        else {
          gGetChar = '\0' ;
          gColumn++ ;   
        } // else        
      } // else if
      else if ( chartoString == "(" || chartoString == ")" ) {
        if ( getString != "" ) {
          bool_true = false ;
        } // if
        else {
          store_line = gLine ;
          store_column = gColumn ;
          gGetChar = '\0' ;
          gColumn++ ;
          getString = chartoString ;
          bool_true = false ;
        } // else 
      } // else if 
      else if ( chartoString == "\'" ) {
        if ( getString != "" ) 
          bool_true = false ;
        else {
          store_line = gLine ;
          store_column = gColumn ;
          gGetChar = '\0' ;
          gColumn++ ;
          getString = chartoString ;
          bool_true = false ;
        } // else 
      } // else if
      else if ( IsDoubleQUOTE( chartoString ) ) {
        if ( getString != "" ) 
          bool_true = false ;

        else {
          store_line = gLine ;
          store_column = gColumn ;
          gGetChar = '\0' ;
          gColumn++ ;
          getString = chartoString ;
          exception_string = true ;
        } // else
      } // else if
      else if (  chartoString.at(0) == ';' ) {
        if ( getString != "" )
          bool_true = false ;
        else {
          gGetChar = '\0' ;
          gColumn++ ;
          exception_semi = true ;              
        } // else
      } // else if
      else {
        if ( store_line == 0 && store_column == 0 ) {
          store_line = gLine ;
          store_column = gColumn ;
        } // if

        gGetChar = '\0' ;
        gColumn++ ;
        getString = getString + chartoString ;
      } // else

    } // while 

    KeyDefine temp( GetType( getString ), getString, store_line, store_column ) ; 

    return temp ;

  } // GetToken()

  bool Parser_atom( ) { 
  /**
   *
    * <ATOM> ::= SYMBOL
    *           | INT 
    *           | FLOAT 
    *           | STRING
    *           | NIL 
    *           | T 
    *           | LEFT-PAREN RIGHT-PAREN
  */
    if ( gToken.GetType() == NONE ) 
      gToken = GetToken() ;

    NodeType type = gToken.GetType() ;
    
    if ( type == SYMBOL ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == INT ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == FLOAT ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == STRING ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == NIL ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == T ) 
      gDealToken.push_back( gToken ) ;
    else if ( type == LEFT_PAREN ) {
      try {
        gToken = GetToken() ;
      } // try
      catch( int num ) {
        if ( num == 1 ) { 
          if ( MODE )  cout << "throw 1 EOF" ;
          throw 1 ;
        } // if
        else if ( num == 2 ) { 
          if ( MODE )  cout << "throw 2 string error " ;
          throw 3 ;
        } // else if
        else 
          cout << "Unknown error in AtoM() " << endl ;
      } // catch

      if ( gToken.GetType() == RIGHT_PAREN ) {
        gDealToken.push_back( gToken ) ;
        gToken.SetType( NONE ) ;
      } // if        
      else {
        return false ;
      } // else 
    } // else if
    else {
      return false ;
    } // else 

    gToken.SetType( NONE ) ;
    return true ;
  } // Parser_atom()

  bool Parser_Sexp() {
  /**
    * <S-exp> ::= <ATOM> 
    *            | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
    *            | QUOTE <S-exp>
    *
    *  Remark : {} <- 0 or more
    *           [] <- 0 or 1 
  */
    try {
      if ( gToken.GetType() == NONE ) 
        gToken = GetToken() ;



      if ( gToken.GetType() == LEFT_PAREN ) {
        gDealToken.push_back( gToken ) ;
        if ( Parser_atom() ) {
          return true ;
        } // if

        if ( Parser_Sexp() ) {
          gToken = GetToken() ;
          while ( gToken.GetType() != DOT && gToken.GetType() != RIGHT_PAREN ) {
            if ( ! Parser_Sexp() ) 
              throw 3 ;
            // if ( gToken.GetType() == NONE )
            gToken = GetToken() ;
          } // while

          if ( gToken.GetType() == DOT ) {
            gDealToken.push_back( gToken ) ;
            gToken.SetType( NONE ) ;
            if ( ! Parser_Sexp() ) 
              throw 3 ;

            gToken = GetToken() ;
          } // if

          if ( gToken.GetType() == RIGHT_PAREN ) {
            gDealToken.push_back( gToken ) ;
            gToken.SetType( NONE ) ;
            return true ;
          } // if
          else {
            cout << "ERROR (unexpected token) : ')' expected when token at Line " 
                  << gToken.GetLine() << " Column " << gToken.GetColumn() << " is >>" 
                  << gToken.GetKey() << "<<" << endl ;
            throw 3 ;
          } // else 
        } // if
        else {
          throw 3 ;
        } // else
          // throw 3 ;
      } // if
      else if ( gToken.GetType() == SINGLE_QUOTE ) {
        gDealToken.push_back( gToken ) ;
        gToken.SetType( NONE ) ;
        if ( Parser_Sexp() ) 
          return true ;
        else {
          cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " 
          << gToken.GetLine() << " Column " << gToken.GetColumn() << " is >>" 
          << gToken.GetKey() << "<<" << endl ;
          throw 3 ;
        } // else 
      } // else if
      else if ( Parser_atom() ) {
        return true ;
      } // if
      else {
        cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " 
            << gToken.GetLine() << " Column " << gToken.GetColumn() << " is >>" 
            << gToken.GetKey() << "<<" << endl ;
        return false ;
      } // else 

      return false ;
    } // try
    catch ( int num ) {
      if ( num == 1 ) // EOF
        throw 1 ;
      else if ( num == 2 ) // string error
        return false ;
      else if ( num == 3 ) // sexp error 
        return false ;
      else 
        cout << "Unknown error in Parser_exp() " << endl ;
    } // catch 

    return false ;
  } // Parser_Sexp() 

  void Merge_Quote_nil() { // origin : DetectAtoM() 

    for ( int i = gDealToken.size() - 1  ; i > 0 ; i-- ) {
      if ( gDealToken[i-1].GetType() == LEFT_PAREN && gDealToken[i].GetType() == RIGHT_PAREN ) {
        gDealToken[i-1].SetType( NIL ) ;
        gDealToken[i-1].SetKey( "()" ) ;
        gDealToken.erase( gDealToken.begin()+i ) ;
      } // if
    } // for


    // if ( gDealToken.size() == 1 ) {
    //   if ( MODE ) {
    //     cout << "[info] in DetectAtoM()  atom!!" << endl ;
    //   } // if

    //   gDealToken.front().PrintKey( true ) ;
    //   throw 2 ;
    // } // if
  } // DetectAtoM()

  bool Parser_Interface() {  // set gDealToken
  /**
  // <S-exp> ::= <ATOM> 
  //         | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
  //         | QUOTE <S-exp>

  // <ATOM>  ::= SYMBOL | INT | FLOAT | STRING 
  //         | NIL | T | LEFT-PAREN RIGHT-PAREN
  */

    try {
      if ( Parser_Sexp() )  
        return true ;
      else {
        while ( gGetChar != '\n' ) {
          scanf( "%c", &gGetChar ) ;
        } // while

        gGetChar = '\0' ;
        throw 3 ;
      } // else
    } // try
    catch ( int no ) {
      if ( no == 1 )  // EOF encounter
        throw 1 ;
      else if ( no == 3 ) // error
        throw 3 ;
      else 
        cout << "There is a known error in Parser_Interface()" << endl ;
    } // catch
    return false ;

  } // Parser_Interface()





  public : 

  void ReadSExp() {
    try {
      Parser_Interface() ;    // Should set gDealToken() ;

      Merge_Quote_nil() ;  
    } // try
    catch ( int no ) {
      if ( no == 0 ) // exit
        throw 0 ;
      if ( no == 1 ) // EOF encounter 
        throw 1 ;
      // else if ( no == 2 ) // atom
      //   throw 2 ;
      else if ( no == 3 ) // error
        throw 3 ;
      else 
        cout << " There is a known error in ReadSExp()" << endl ;
    } // catch
  } // ReadSExp() 
}; // Read_Exp



class Build_Tree_Exp {
  // public:

  void DetectExit( ) {
    if ( g_Tree != NULL ) {
      if ( g_Tree->m_left != NULL ) {
        if ( g_Tree->m_left->m_key.GetType() == SYMBOL && g_Tree->m_left->m_key.GetKey() == "exit" ) {
          if ( g_Tree->m_right == NULL ) {
            throw 0 ;
          } // if
          else if ( g_Tree->m_right->m_key.GetType() == NIL ) {
            throw 0 ;
          } // if
        } // if
      } // if
    } // if
  } // DetectExit()

  void GetItem( vector<KeyDefine> & tokenchain, vector<KeyDefine> & item ) {

    bool get_one = false ;
    int count_paren = 0 ;
    bool bool_true = true ;
    bool exception_single_quote = false ;
    item.clear() ;
    if ( MODE ) {
      cout << "Debug in GetItem()   tokenchain :" ;
      for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
        cout << tokenchain[i].GetKey() << " " ;
      } // for

    cout << endl ;      
    } // if

    while ( count_paren != 0 || ! get_one ) {
      get_one = true ;
      if ( tokenchain.front().GetType() == LEFT_PAREN ) 
        count_paren++ ;
      else if ( tokenchain.front().GetType() == RIGHT_PAREN ) 
        count_paren-- ;
      
      item.push_back( tokenchain.front() ) ;
      tokenchain.erase( tokenchain.begin() ) ;
    } // while      


    if ( MODE ) {
      cout << "   Debug in GetItem()   Get :" ;
      for ( int i = 0 ; i < item.size() ; i++ ) {
        cout << item[i].GetKey() << " " ;
      } // for

    cout << endl ;      
    } // if

  } // GetItem()

  void Build_tree_De_Paren( Tree * & head, vector <KeyDefine> & tokenchain ) {

    if ( tokenchain.front().GetType() == LEFT_PAREN && tokenchain.back().GetType() == RIGHT_PAREN ) {
      tokenchain.erase( tokenchain.begin() ) ;
      tokenchain.erase( tokenchain.end() ) ;
    } // if

    BuildTree( head, tokenchain ) ;
  } // Build_tree_De_Paren()

  void BuildTree( Tree * & head, vector<KeyDefine> & tokenchain ) {
    // 只遞迴Internal Node   

    head = new Tree() ;

    KeyDefine internal( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
    head->m_key = internal ;
    vector<KeyDefine> item ;

    GetItem( tokenchain, item ) ;   // item.clear()

    if ( item.size() == 1 ) {
      if ( item.front().GetType() == SINGLE_QUOTE ) {
        if ( head == g_Tree ) {
          head->m_left = new Tree() ;
          head->m_left->m_key = item.front() ;
        } // if
        else {
          vector<KeyDefine> another_sexp, temp ;
          GetItem( tokenchain, another_sexp ) ;
          if ( another_sexp.front().GetType() == SINGLE_QUOTE ) {
              GetItem( tokenchain, temp ) ;
            while ( temp.front().GetType() == SINGLE_QUOTE ) {
              another_sexp.push_back( temp.front() ) ;
              GetItem( tokenchain, temp ) ;              
            } // while           
            
            while ( ! temp.empty() ) {
              another_sexp.push_back( temp.front() ) ;
              temp.erase( temp.begin() ) ; 
            } // while
          } // if

          head->m_left = new Tree() ;
          head->m_left->m_key = internal ;
          head->m_left->m_left = new Tree() ;
          head->m_left->m_left->m_key = item.front() ;
          BuildTree( head->m_left->m_right, another_sexp ) ;
        } // else 
      } // if
      else {
        head->m_left = new Tree() ;
        head->m_left->m_key = item.front() ;        
      } // else
    } // if
    else 
      Build_tree_De_Paren( head->m_left, item ) ;


    if ( ! tokenchain.empty() ) {
      if ( tokenchain.front().GetType() == DOT ) {
        GetItem( tokenchain, item ) ;   // item.clear()  (DOT)
        GetItem( tokenchain, item ) ;   // item.clear()
        if ( item.size() == 1 ) {
          head->m_right = new Tree() ;
          head->m_right->m_key = item.front() ;
        } // if
        else 
          Build_tree_De_Paren( head->m_right, item ) ;
      } // if
      else 
        BuildTree( head->m_right, tokenchain ) ;
    } // if

  } // BuildTree()





  public:

  void BuildTree_Interfaces( vector<KeyDefine> token_list ) { // build tree base on token_list (gDealtoken's reserve)

    if ( token_list.front().GetType() == SINGLE_QUOTE ) 
      BuildTree( g_Tree, token_list ) ; 
    else 
      Build_tree_De_Paren( g_Tree, token_list ) ;



    try {
      DetectExit() ;  // if (exit), throw 0.
    } // try
    catch ( int num ) {
      if ( num == 0 ) 
        throw 0 ;
    } // catch

  } // BuildTree_Interfaces()
}; // Build_Tree_Exp


class Evaluate_Exp {
 // error : throw 4

  Tree * GetBinding( string name ) {
    for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
      if ( g_Define_Binding.at( i )->m_left->m_key.GetKey() == name ) {
        if ( g_Define_Binding.at( i )->m_right->m_left->m_key.GetKey() == "quote" || 
             g_Define_Binding.at( i )->m_right->m_left->m_key.GetType() == SINGLE_QUOTE )
          return g_Define_Binding.at( i )->m_right->m_right->m_left ;
        else 
          return g_Define_Binding.at( i )->m_right->m_left ;
      } // if
    } // for
    return NULL ;
  } // GetBinding()

  void InsertDefine( string name, Tree * tree ) {
    bool repeat = false ;
    for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
      if ( g_Define_Binding.at( i )->m_left->m_key.GetKey() == name ) {
        repeat = true ;
        delete g_Define_Binding.at( i ) ;
        g_Define_Binding.at( i ) = tree ;
      } // if
    } // for

    if ( ! repeat ) 
      g_Define_Binding.push_back( tree ) ;

    cout << name << " defined" << endl ;
  } // InsertDefine

  Tree * Evaluate_Constructors( Tree * head, string type ) {
    // cons (2)
    // (將前面的成員推入後面的list) 、(若後面非list,則2個成員將組成一個pair) 

    // list (>= 0)
    // 將參數列轉為list 
    Tree * evaluate = NULL ;
    Tree * walk_head = head ;
    Tree * walk_evaluate = evaluate ;

    if ( type == "cons" ) {
      int count = 0 ;
      while ( walk_head != NULL ) {
        if ( walk_head->m_left->m_key.GetType() == INTERNAL_NODE ) {
          ; // not implement
        } // if
        else if ( walk_head->m_left->m_key.GetType() == SINGLE_QUOTE ||
                  walk_head->m_left->m_key.GetKey() == "quote" ) {
          ; // not implement
        } // else if
        else {
          if ( evaluate == NULL ) {
            evaluate = new Tree() ;
            evaluate->m_key.SetType( INTERNAL_NODE ) ;
            walk_evaluate = evaluate ;         
            walk_evaluate->m_left = walk_head->m_left ;   
          } // if
          else {
            walk_evaluate->m_right = walk_head->m_left ;
          } // else

        } // else
        walk_head = walk_head->m_right ;
      } // while



      if ( count != 2 ) {
        cout << "Error in cons(), parameter is NOT 2 " << endl ;
        throw 4 ;
      } // if

    } // if
    else if ( type == "cons" ) {

    } // else if
    else {
      cout << "UnKnown type in Evaluate_Constructors()" << endl ;
    } // else

    return evaluate ;
  } // Evaluate_Constructors()

  Tree * Evaluate_Quote( Tree * head ) {
    // quote (1)    將list視為資料而不評估它 
    // '     (1)
    if ( head == NULL ) {
      cout << "Error in Quote, quote does not have parameters" << endl ;
    } // if
    else {
      return head->m_left ;
    } // else
  } // Evaluate_quote()

  void Evaluate_Define( Tree * head, string type ) {
    // define (2)
    // cannot define keywords
    // cons  list  quote  define  car  cdr  atom  pair  list  null  integer  real  number  string  boolean  symbol  + - * /  not  and  or  string-append  string>?  string<?  string=?  begin  if  cond  clean-environment
    int count = 0 ;
    Tree * walk_head = head ;
    while( walk_head != NULL ) {
      if ( walk_head->m_left->m_key.GetType() != SINGLE_QUOTE &&
           walk_head->m_left->m_key.GetKey() != "quote" ) {
          count++ ;
      } // if
      walk_head = walk_head->m_right ;
    } // while

    if ( count == 2 ) {
      InsertDefine( head->m_left->m_key.GetKey(), head ) ;
    } // if 
    else {
      cout << "[Error] Evaluate_Define 's parameter is NOT 2" << endl ;
    } // else
  } // Evaluate_Define()

  Tree * Evaluate_Part_Accessors( Tree * head, string type ) {
    // car (1) (從list之中抓出第一個成員) 
    // cdr (1) (去除第一個成員後的list) 
    

  } // Evaluate_Part_Accessors()

  bool Evaluate_is_primitive( Tree * head, string type ) {
    // atom? (1)

    // pair? (1)

    // list? (1)

    // null? (1)

    // integer? (1)

    // real? (=number) (1)

    // number? (= real) (1)

    // string? (1)

    // boolean? (1)

    // symbol? (1)
  } // Evaluate_primitive()

  Tree * Evaluate_Basic_arithmetic( Tree * head, string type ) {
    // +(>= 2)

    // -(>= 2)

    // *(>= 2)

    // /(>= 2)

    // not (1)

    // and(>= 2)

    // or(>= 2)




    // >   (>= 2)

    // >=   (>= 2)

    // <   (>= 2)

    // <=  (>= 2)

    // =   (>= 2)

    // string-append(>= 2)

    // string>?(>= 2)

    // string>?(>= 2)

    // string=?(>= 2)

  } // Evaluate_Basic_arithmetic

  bool Evaluate_Eqivalence_tester( Tree * head, string type ) {
    // eqv?    (2)

    // equal?  (2)
  } // Evaluate_Eqivalence_tester()

  Tree * Evaluate_Sequencing_and_functional_composition( Tree * head, string type ) {
    // begin   (>= 1)

  } // Evaluate_Sequencing_and_functional_composition()

  Tree * Evaluate_Conditionals( Tree * head, string type ) {
    // if     (2 or 3)

    // cond   (>= 1)

  } // Evaluate_Conditionals()

  void Clean_Environment( Tree * head ) {
    // clean-environment   (0)
    // care : 參數傳遞   

    if ( head->m_right != NULL || head->m_right != NULL) {
      cout << "error in clean_environment, too much parameter" << endl ;
      throw 4 ;
    } // if

    for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
      delete g_Define_Binding.at( i ) ;
    } // for

    g_Define_Binding.clear() ;
    cout << "environment-cleaned" << endl ;
  } // Clean_Environment()





  public:

  Tree * Eval_SExp( Tree * tree ) {
    string operate_type = tree->m_left->m_key.GetKey() ;
    Tree * result ;

    try{

      if ( operate_type == "cons" || operate_type == "list" ) {
        result = Evaluate_Constructors( tree->m_right, operate_type) ;
      } // if
      else if ( operate_type == "quote" || operate_type == "\'" ) {
        result = Evaluate_Quote( tree->m_right) ;
      } // else if 
      else if ( operate_type == "define" ) {  
        Evaluate_Define( tree->m_right, operate_type) ;
        throw 2 ;
      } // else if
      else if ( operate_type == "car" || operate_type == "cdr" ) {
        result = Evaluate_Part_Accessors( tree->m_right, operate_type) ;
      } // else if
      else if ( operate_type == "atom?" || operate_type == "pair?" || operate_type == "list?" ||
                operate_type == "null?" || operate_type == "integer?" || operate_type == "real?" ||
                operate_type == "number?" || operate_type == "string?" || operate_type == "boolean?" || 
                operate_type == "symbol?" ) {
        if ( Evaluate_is_primitive( tree->m_right, operate_type) )
          cout << "#t" << endl ;
        else 
          cout << "nil" << endl ;
      } // else if
      else if ( operate_type == "+" || operate_type == "-" || operate_type == "*" || operate_type == "/" ||
                operate_type == "not" || operate_type == "and" || operate_type == "or" ||
                operate_type == ">" || operate_type == ">=" || operate_type == "<" || operate_type == "<=" ||
                operate_type == "=" || operate_type == "string-append"  || 
                operate_type == "string>?" || operate_type == "string<?" || operate_type == "string=?" ) {
        result = Evaluate_Basic_arithmetic( tree->m_right, operate_type) ;
      } // else if
      else if ( operate_type == "eqv?" || operate_type == "equal?" ) {
        if ( Evaluate_Eqivalence_tester( tree->m_right, operate_type) )
          cout << "#t" << endl ;
        else
          cout << "nil" << endl ;        
      } // else if
      else if ( operate_type == "begin" ) {
        result = Evaluate_Sequencing_and_functional_composition( tree->m_right, operate_type) ;
      } // else if
      else if ( operate_type == "if" || operate_type == "cond" ) {
        result = Evaluate_Conditionals( tree->m_right, operate_type) ;
      } // else if
      else if ( operate_type == "clean-environment" ) {  // throw 2
        Clean_Environment( tree->m_right ) ;
        throw 2 ;
      } // else if
      else if ( tree->m_left->m_key.GetType() == SYMBOL && tree->m_right == NULL ) {
        result = GetBinding( tree->m_left->m_key.GetKey() ) ;
        
        if ( result == NULL ) {
          cout << "No Define " << tree->m_left->m_key.GetKey() << endl ;
          throw 4 ;
        } // if
      } // else if
      else {
        cout << "[Error] : No type found in Eval_SExp()" ;
        throw 4 ;
      } // else
    } // try
    catch( int num ) {

      if ( num == 4 ) {
        cout << "Catch Error in Eval_SExp()" << endl ;
        throw 4 ;
      } // if
      else if ( num == 2 ) {
        cout << "Pass!" << endl ;
        throw 2 ;
      } // else if
      else {
        cout << "There have a known error in Eval_SExp()" << endl ;
      } // else
    } // catch



    return result ;
  } // Eval_SExp()

}; // Evaluate_Exp


class Print_Exp {

  void PrintSpace( int count ) {
    for ( int i = 0 ; i < 2 * count ; i++ ) {
      cout << " " ; 
    } // for
  } // PrintSpace()

  void Print_Function_SingleQuote( Tree * result ) {

    Print( result, 0 ) ;

  } // Print_Function_SingleQuote() 

  void Print_Normal( Tree * result ) {
    cout << "( " ;
    Print( result, 1 ) ;
    cout << ")" << endl ;
  } // Print_Normal()

  void Print1( Tree * head, int count ) { 
    bool check = true ;
    int count_exception = 0 ;
    bool exception_single_quote = false ;
    while ( check ) {
      if ( head->m_left->m_key.GetType() == SINGLE_QUOTE ) {
        exception_single_quote = true ;
        count_exception++ ;
        cout << "( quote" << endl ; 
      } // if
      else {
        // -------------------------------------------------------------------
        if ( head->m_left->m_key.GetType() == INTERNAL_NODE ) {
          if ( exception_single_quote ) {

            // count_exception++ ;
            cout << "( " ;
            Print( head->m_left, count+count_exception+1 ) ; // +1
            PrintSpace( count+count_exception ) ; 
            cout << ")" << endl ;
            while ( count_exception > 0 ) { 
              count_exception-- ;
              PrintSpace( count+count_exception ) ;
              cout << ")" << endl ;
            } // while
          } // if
          else {
            cout << "( " ;
            Print( head->m_left, count+1 ) ;
            PrintSpace( count ) ;
            cout << ")" << endl ;
          } // else
        } // if

        // -------------------------------------------------------------------

        else {                       // NOT single_quote   // NOT internal_node
          if ( exception_single_quote ) {
            // count_exception++ ;
            head->m_left->m_key.PrintKey( true ) ;
            while ( count_exception > 0 ) {            
              count_exception-- ;
              PrintSpace( count+count_exception ) ; // not-1
              cout << ")" << endl ;
            } // while
          } // if
          else {
            head->m_left->m_key.PrintKey( true ) ;
            while ( count_exception > 0 ) { 
              count_exception-- ;
              PrintSpace( count+count_exception-1 ) ;
              cout << ")" << endl ;
            } // while
          } // else 
        } // else



        if ( head->m_right != NULL ) {  //             --------------- print right pattern
          if ( head->m_right->m_key.GetType() != NIL && head->m_right->m_key.GetType() != INTERNAL_NODE ) {
            PrintSpace( count );
            cout << "." << endl ;
            PrintSpace( count ) ;
            head->m_right->m_key.PrintKey( true ) ;
            check = false ;
          } // if
        } // if

        exception_single_quote = false ;
      } // else

      if ( ! check ) 
        ;
      else if ( head->m_right == NULL ) 
        check = false ;
      else if ( head->m_right->m_key.GetType() == NIL ) 
        check = false ;
      else {
        head = head->m_right ;
        if ( exception_single_quote ) 
          PrintSpace( count+count_exception ) ; // -1
        else 
          PrintSpace( count ) ; // not -1---------------------------------
      } // else
        
    } // while
  } // Print()

  void Print( Tree * head, int count ) {
    bool check = true ;
    int count_exception = 0 ;

    while ( check ) {
      if ( head->m_left->m_key.GetType() == INTERNAL_NODE ) {
        cout << "( " ;
        Print( head->m_left, count+1 ) ;
        PrintSpace( count ) ;
        cout << ")" << endl ;
      } // if
      else {
        head->m_left->m_key.PrintKey( true ) ;
      } // else

      if ( head->m_right == NULL ) {
        check = false ;
      } // if
      else if ( head->m_right->m_key.GetType() != INTERNAL_NODE ) {
        if ( head->m_right->m_key.GetType() == NIL ) 
          check = false ;
        else {
          PrintSpace( count ) ;
          cout << "." << endl ;
          PrintSpace( count ) ;
          head->m_right->m_key.PrintKey( true ) ;
          check = false ;
        } // else
      } // else if
      else {
        head = head->m_right ;
        PrintSpace( count ) ;
      } // else

    } // while
  } // Print()



  public:

  void ViolatePrint( Tree * head, int count ) {
    for ( int i = 1 ; i < count ; i++ ) {
      cout << " " ;
    } // for

    head->m_key.PrintKey( true ) ;

    if ( head->m_left != NULL ) {
      cout << "left" << endl ;
      ViolatePrint( head->m_left, count+1 ) ;
    } // if
    
    if ( head->m_right != NULL ) {
      cout << "right" << endl ;
      ViolatePrint( head->m_right, count+1 ) ;
    } // if

    cout << "end a node" << endl ;
  } // ViolatePrint()  

  void PrintSExp( Tree * result ) {
    // if ( result == NULL ) 
    //   printf("Error in result!  result is NULL") ;
    // else if ( result->m_key.GetType() != INTERNAL_NODE ) 
    //   cout << result->m_key.GetKey() << endl ;
    // else {
    //   Print_Normal(result) ;
    // } // else

    Print_Normal( result ) ;
  } // PrintSExp()

} ; // Print_Exp



int main() {

  Read_Exp read_exp ;
  Build_Tree_Exp build_exp ;
  Evaluate_Exp evaluate_exp ;
  Print_Exp print_exp ;

  vector<KeyDefine> keylist ;
  cout << "Welcome to OurScheme!" << endl ;
  cout << "\n" ;
  char onechar ;

  if ( MODE )
    cout << "[debug] Please enter a gTestNum :" ;
  cin >> gTestNum ;


  setbuf(stdin, NULL) ; //  IDE : Visual Studio Code

  bool bool_true = true ;
  while ( bool_true ) {
    try {
      cout << "> " ;
      gLine = 0 ; 
      gColumn = 1 ;
      gDealToken.clear() ;
      gToken.SetType( NONE ) ;
      delete g_Tree ;
      g_Tree = NULL ;
      delete g_Result ;
      g_Result = NULL ;
      if ( MODE )   cout << "------   -------------- ------------ ---------------- INIT() ----  " << endl ;
      read_exp.ReadSExp() ;  // if Syntax Error, throw exception
      build_exp.BuildTree_Interfaces( gDealToken ) ;  // build tree base on gDealToken() , if (exit) throw 0
      if ( MODE ) cout << "BuildTree Success" << endl ;
      if ( MODE ) {
        if ( g_Tree == NULL ) {
          cout << "g_tree is NULL" << endl ;
        } // if
      } // if
      // g_Result = evaluate_exp.Eval_SExp( g_Tree ) ;  // if Evalution error, throw exception
      // if ( MODE ) cout << "Evaluate Success" << endl ;
      // print_exp.PrintSExp( g_Result ) ;  // print_tree( base on g_tree)

      // print_exp.ViolatePrint( g_Tree, 1 ) ;

      print_exp.PrintSExp( g_Tree ) ;
      cout << endl  ;
    } // try
    catch( int num ) {
      if ( num == 0 ) {    // (exit)
        cout << endl ;
        bool_true = false ;
      } // if
      else if ( num == 1 ) {    // EndOfFile
        cout << "ERROR (no more input) : END-OF-FILE encountered" << endl ;
        bool_true = false ; 
      } // if
      else if ( num == 2 ) {   // pass 
        cout << endl ;
      } // else if
      else if ( num == 3 ) {  // syntax error + string error
        cout << endl ;
      } // else if 
      else if ( num == 4 ) {
        cout << "Have error in evaluation()" << endl; 
        cout << endl ;
      } // else if
      else {
        cout << "There is a known error in main()" << endl ;
      } // else
    } // catch
  } // while
  
  cout << "Thanks for using OurScheme!"  ;
 
} // main()