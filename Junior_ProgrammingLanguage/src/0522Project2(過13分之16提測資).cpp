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



bool Is_Keywords( string keywords ) {
  if ( keywords == "cons" || keywords == "list" || keywords == "quote" || keywords == "define" || 
       keywords == "car" || keywords == "cdr" || keywords == "atom?" || keywords == "pair?" || 
       keywords == "list?" || keywords == "null?" || keywords == "integer?" || keywords == "real?" || 
       keywords == "number?" || keywords == "string?" || keywords == "boolean?" || keywords == "symbol?" || 
       keywords == "+" || keywords == "-" || keywords == "*" || keywords == "/" || 
       keywords == "not" || keywords == "and" || keywords == "or" || keywords == ">" ||
       keywords == ">=" || keywords == "<" || keywords == "<=" || keywords == "=" ||  
       keywords == "string-append" || keywords == "string>?" || keywords == "string<?" || 
       keywords == "string=?" || keywords == "eqv?" || keywords == "equal?" || keywords == "begin" ||
       keywords == "if" || keywords == "cond" || keywords == "clean-environment" || keywords == "exit"
     ) 
    return true ;
  else 
    return false ;
} // Is_Keywords()

bool Is_Zero( string a ) {
  // depend on int and float 
  for ( int i = 0 ; i < a.size() ; i++ ) {
    if ( a[i] != '-' && a[i] != '0' && a[i] != '.' ) 
      return false ;
  } // for

  return true ;
} // Is_Zero()

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

char Int_to_Char( int a ) {
  if ( a == 0 ) return '0' ;
  else if ( a == 1 ) return '1' ;
  else if ( a == 2 ) return '2' ;
  else if ( a == 3 ) return '3' ;
  else if ( a == 4 ) return '4' ;
  else if ( a == 5 ) return '5' ;
  else if ( a == 6 ) return '6' ;
  else if ( a == 7 ) return '7' ;
  else if ( a == 8 ) return '8' ;
  else if ( a == 9 ) return '9' ;
  else return 'x';
} // Int_to_Char()

float String_To_Float( string str ) {
  // 銝恣蝎暹?摨圩f

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

int String_to_Int( string str ) {
  int sum = 0 ;
  bool neg = false ;
  for ( int i = 0 ; i < str.size() && str[i] != '.' ; i++ ) {
    if ( str[i] == '-' )  
      neg = true ;
    else
      sum = sum * 10 + Char_To_Int( str[i] ) ;
  } // for

  if ( neg )
    sum = sum * -1 ;

  return sum ;
} // String_to_Int()

string Int_to_String( int a ) {
  int base = 1 ;
  string store = "" ;
  bool neg = false ;
  
  if ( a < 0 ) {
    neg = true ;
    a = a * -1 ;
  } // if

  while ( base * 10 <= a ) {
    base = base * 10 ;
  } // while


  while ( base >= 1 ) {
    int quo = 0 ;
    while ( base <= a ) {
      quo++ ;
      a = a - base ;
    } // while

    store = store + Int_to_Char( quo ) ;
    base = base / 10 ;
  } // while

  if ( neg ) 
    store = "-" + store ;

  return store ;
  // return to_string(a) ;
} // Int_to_String()


string Float_to_String( float a ) {
  float base = 1 ;
  string store = "" ;
  bool neg = false ;
  
  if ( a < 0 ) {
    neg = true ;
    a = a * -1 ;
  } // if

  while ( base * 10 <= a ) { 
    base = base * 10 ;
  } // while


  while ( base >= 1 ) {
    int quo = 0 ;
    
    while ( base <= a ) {
      quo++ ;
      a = a - base ;
    } // while

    store = store + Int_to_Char( quo ) ;
    base = base / 10 ;
  } // while

  store = store + "." ;

  while ( a != 0 && store.size() < 10 ) {
    int quo = 0 ;
      
    
    while ( base <= a ) {
      quo++ ;
      a = a - base ;
    } // while

    store = store + Int_to_Char( quo ) ;
    base = base / 10 ;
  } // while

  if ( neg ) 
    store = "-" + store ;

  return store ;
  // return to_string(a) ;
} // Float_to_String()

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
  bool m_key_protect ;

  public :
  KeyDefine() { 
    m_key_protect = false ;
  } // KeyDefine()    

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

  void SetProtect( bool true_or_false ) {
    m_key_protect = true_or_false ;
  } // SetProtect()

  bool GetProtect() {
    return m_key_protect ;
  } // GetProtect()
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
    // cout << "---" << endl ;
    while ( bool_true ) {

      if ( gGetChar != '\0' ) 
        ;
      else {
        gGetChar = getchar() ;
        if ( gGetChar == EOF ) 
          throw 1 ;
      } // else
      // else if ( scanf( "%c", &gGetChar ) == EOF ) {
      // cout << "Detect " << gGetChar << endl ;
      //   throw 1 ;
      // } // else if 
    
      chartoString = gGetChar ;
      
      // cout << "Detect Not EOF" << chartoString << endl ;
      
      if ( exception_semi ) {  
        // cout << "Get into exception_semi" << endl ;
        gGetChar = '\0' ;
        if ( chartoString == "\n" ) {
          
          if ( round_one ) {
            gLine = 1 ;
            round_one = false ; 
          } // if
          else
            gLine++ ;
          gColumn = 1 ;
          // cout << "563" << endl ;
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
      else if ( chartoString.at( 0 ) == ';' ) {
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
    if ( gToken.GetType() == NONE ) {
      // cout << "atom gettoken1() " << endl ;
      gToken = GetToken() ;
    } // if
      

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
        // cout << "atom gettoken2() " << endl ;
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
      if ( gToken.GetType() == NONE ) {
        gToken = GetToken() ;
      } // if
        



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
        throw 3 ;
      } // else 

      return false ;
    } // try
    catch ( int num ) {
      if ( num == 1 ) // EOF
        throw 1 ;
      else if ( num == 2 ) // string error
        throw 3 ;
      else if ( num == 3 ) // sexp error 
        throw 3 ;
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


    if ( gDealToken.size() == 1 ) {
      if ( MODE ) {
        cout << "[info] in DetectAtoM()  atom!!" << endl ;
      } // if

      // gDealToken.front().PrintKey( true ) ;
      throw 5 ;
    } // if
  } // Merge_Quote_nil()

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
      // else {
      //   while ( gGetChar != '\n' ) {
      //     gGetChar = getchar() ;
      //     // scanf( "%c", &gGetChar ) ;
      //   } // while

      //   gGetChar = '\0' ;
      //   throw 3 ;
      // } // else
    } // try
    catch ( int no ) {
      if ( no == 1 )  // EOF encounter
        throw 1 ;
      else if ( no == 3 ) { // error
        while ( gGetChar != '\n' && gGetChar != EOF ) {
          gGetChar = getchar() ;
          // scanf( "%c", &gGetChar ) ;
        } // while

        gGetChar = '\0' ;
        throw 3 ;
      } // else if
      else 
        cout << "There is a known error in Parser_Interface()" << endl ;
    } // catch
    return false ;

  } // Parser_Interface()

  public : 

  void ReadSExp() {
    try {
      Parser_Interface() ;    // Should set gDealToken() ;

      Merge_Quote_nil() ;  // and detect atom


    } // try
    catch ( int no ) {
      if ( no == 0 ) // exit
        throw 0 ;
      if ( no == 1 ) // EOF encounter 
        throw 1 ;
      else if ( no == 5 ) // atom
        throw 5 ;
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

    while ( count_paren != 0 || ! get_one ) {
      get_one = true ;
      if ( tokenchain.front().GetType() == LEFT_PAREN ) 
        count_paren++ ;
      else if ( tokenchain.front().GetType() == RIGHT_PAREN ) 
        count_paren-- ;
      
      item.push_back( tokenchain.front() ) ;
      tokenchain.erase( tokenchain.begin() ) ;
    } // while      

  } // GetItem()

  Tree * Build_tree_De_Paren( bool & is_head, vector <KeyDefine> & tokenchain ) {

    if ( tokenchain.front().GetType() == LEFT_PAREN && tokenchain.back().GetType() == RIGHT_PAREN ) {
      tokenchain.erase( tokenchain.begin() ) ;
      tokenchain.erase( tokenchain.end() ) ;
    } // if

    return BuildTree( is_head, tokenchain ) ;
  } // Build_tree_De_Paren()

  Tree *  BuildTree( bool & is_head, vector<KeyDefine> & tokenchain ) {
    // ?芷?餈富nternal Node   

    Tree * head = new Tree() ;

    KeyDefine internal( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
    head->m_key = internal ;
    vector<KeyDefine> item ;

    GetItem( tokenchain, item ) ;   // item.clear()
    bool is_head_store = is_head ;
    is_head = false ;

    if ( item.size() == 1 ) {
      if ( item.front().GetType() == SINGLE_QUOTE ) {
        if ( is_head_store ) {
          head->m_left = new Tree() ;
          head->m_left->m_key = item.front() ;
          is_head = false ;
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
          head->m_left->m_right =  BuildTree( is_head, another_sexp ) ;
        } // else 
      } // if
      else {
        head->m_left = new Tree() ;
        head->m_left->m_key = item.front() ;        
      } // else
    } // if
    else 
      head->m_left = Build_tree_De_Paren( is_head, item ) ;


    if ( ! tokenchain.empty() ) {
      if ( tokenchain.front().GetType() == DOT ) {
        GetItem( tokenchain, item ) ;   // item.clear()  (DOT)
        GetItem( tokenchain, item ) ;   // item.clear()
        if ( item.size() == 1  ) {   // 
          if ( item.front().GetType() != NIL ) {
            head->m_right = new Tree() ;
            head->m_right->m_key = item.front() ;
          } // if
        } // if
        else 
          head->m_right = Build_tree_De_Paren( is_head, item ) ;
      } // if
      else 
        head->m_right =  BuildTree( is_head, tokenchain ) ;
    } // if

    return head ;
  } // BuildTree()





  public:

  void BuildTree_Interfaces( vector<KeyDefine> token_list ) {
    // build tree base on token_list (gDealtoken's reserve)
    bool is_head = true ;
    if ( token_list.front().GetType() == SINGLE_QUOTE ) 
      g_Tree = BuildTree( is_head, token_list ) ; 
    else 
      g_Tree = Build_tree_De_Paren( is_head, token_list ) ;



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
  Tree * Copy_Tree( Tree * tree ) {
    // ?艘 internalnode
    Tree * copy = NULL ; 
    KeyDefine internalnode( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
    if ( tree == NULL ) {
      cout << "copy tree, tree is null" << endl ;
    } // if
    else if ( tree->m_key.GetType() != INTERNAL_NODE ) {
      copy = new Tree() ;
      copy->m_key = tree->m_key ;
    } // else if
      
    else {
      copy = new Tree() ;
      copy->m_key = internalnode ;
      if ( tree->m_left->m_key.GetType() == INTERNAL_NODE ) 
        copy->m_left = Copy_Tree( tree->m_left ) ;
      else {
        copy->m_left = new Tree() ;
        copy->m_left->m_key = tree->m_left->m_key ;
      } // else
  
      if ( tree->m_right != NULL ) {
        if ( tree->m_right->m_key.GetType() == INTERNAL_NODE ) 
          copy->m_right = Copy_Tree( tree->m_right ) ;
        else {
          copy->m_right = new Tree() ;
          copy->m_right->m_key = tree->m_right->m_key ;
        } // else          
      } // if
    } // else
    
    return copy ;
  } // Copy_Tree()

  Tree * Replace_RepeatSymbol_Define( string name, bool & have_repeat_symbol, 
                                      Tree * tree, Tree * symbol_binding ) {

    if ( tree == NULL ) {
      return NULL ;
      // cout << "Error :  Replace_RepeatSymbol_Define()  tree is NULL" ;
    } // if
    else if ( tree->m_key.GetType() != INTERNAL_NODE ) {
      if ( tree->m_key.GetKey() == name ) {
        tree = symbol_binding ;
        have_repeat_symbol = true ;
      } // if

      return tree ;
    } // else if


    Tree * walk = tree ;
    while ( walk != NULL ) {
      if ( walk->m_left->m_key.GetType() == INTERNAL_NODE ) {
        walk->m_left = Replace_RepeatSymbol_Define( name, have_repeat_symbol, walk->m_left, symbol_binding );
      } // if
      else {
        if ( walk->m_left->m_key.GetKey() == name ) {
          walk->m_left = symbol_binding ;
          have_repeat_symbol = true ;
        } // if
      } // else


      if ( walk->m_right == NULL ) {
        walk = NULL ;
      } // if
      else if ( walk->m_right->m_key.GetType() == INTERNAL_NODE ) {
        walk = walk->m_right ;
      } // else if
      else if ( walk->m_right->m_key.GetType() == NIL ) 
        walk = NULL ;
      else {
        if ( walk->m_right->m_key.GetKey() == name ) {
          walk->m_right = symbol_binding ;
          have_repeat_symbol = true ;
        } // if

        walk = NULL ;
      } // else

    } // while

    return tree ;
  } // Replace_RepeatSymbol_Define()


  void InsertDefine( string name, Tree * tree ) {
    bool repeat = false ;
    for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
      if ( g_Define_Binding.at( i )->m_left->m_key.GetKey() == name ) {
        repeat = true ;

        bool have_repeat_symbol = false ;
        tree->m_right->m_left = Replace_RepeatSymbol_Define( name, have_repeat_symbol, tree->m_right->m_left,
                                                             g_Define_Binding.at( i )->m_right->m_left ) ;
        if ( ! have_repeat_symbol ) {
          delete g_Define_Binding[i] ;
          g_Define_Binding[i] = tree ;
        } // if
        else {
          g_Define_Binding.at( i ) = tree ;
        } // else
        // delete g_Define_Binding.at( i ) ;
        // g_Define_Binding.at( i ) = tree ;
      } // if
    } // for

    if ( ! repeat ) 
      g_Define_Binding.push_back( tree ) ;
    // g_Define_Binding.push_back( tree ) ;
    cout << name << " defined" << endl ;


    g_Result = tree ;
    throw 2 ;
  } // InsertDefine()

  Tree * GetBinding( Tree * head, bool getAddress ) {
    // head->m_key is not internalnode
    if ( head->m_key.GetType() == INTERNAL_NODE ) 
      cout << "Develope Call GetBinding() in wrong way" << endl ;
    else {
      if ( head->m_key.GetType() == SYMBOL && ! Is_Keywords( head->m_key.GetKey() ) ) {
        Tree * binding = GetDefine( head->m_key.GetKey(), getAddress ) ;
        if ( binding == NULL ) {
          cout << "ERROR (unbound symbol) : " << head->m_key.GetKey() << endl ;
          throw 4 ;
        } // if

        return binding ;
      } // if
      else {
        return head ;
      } // else
    } // else
    
    cout << "Unknown Error in GetBinding" << endl ;
    throw 4 ;
    return NULL ;
  } // GetBinding()

  int Count_arguments( Tree * head, bool & dot ) {
    int count = 0 ;
    dot = false ;
    while ( head != NULL ) {
      count++ ;
      if ( head->m_right == NULL ) 
        head = head->m_right ;
      else {
        if ( head->m_right->m_key.GetType() == INTERNAL_NODE ) 
          head = head->m_right ;
        else if ( head->m_right->m_key.GetType() == NIL )
          head = NULL ;
        else if ( head->m_right->m_key.GetType() == SYMBOL ) {
          head->m_right = GetBinding( head->m_right, false ) ;
          if ( head->m_right->m_key.GetType() != NIL ) 
            dot = true ;
          head = NULL ;
        } // else if
        else { 
          head = NULL ;
          dot = true ;
        } // else
      } // else
    } // while

    return count ;
  } // Count_arguments()

  Tree * UnFoldTree( Tree * head, bool getAddress ) {

    Tree * walk = head ;
    while ( walk != NULL ) {
      if ( walk->m_left->m_key.GetType() != INTERNAL_NODE ) {
        walk->m_left = GetBinding( walk->m_left, getAddress ) ;
      } // if
        
      else {
        if ( walk->m_left->m_left->m_key.GetKey() == "clean-environment" ) {
          cout << "ERROR (level of CLEAN-ENVIRONMENT)" << endl ;
          throw 2 ;
        } // if
        else if ( walk->m_left->m_left->m_key.GetKey() == "define" ) {
          cout << "ERROR (level of DEFINE)" << endl ;
          throw 2 ;
        } // if
        else if ( walk->m_left->m_left->m_key.GetKey() == "exit" ) {
          cout << "ERROR (level of EXIT)" << endl ;
          throw 2 ;
        } // else if

        walk->m_left = Eval_SExp( walk->m_left ) ;
      } // else
        
      
      if ( walk->m_right == NULL ) {
        walk = walk->m_right ;
      } // if
      else if ( walk->m_right->m_key.GetType() == INTERNAL_NODE ) {
        walk = walk->m_right ;
      } // else if
      else if ( walk->m_right->m_key.GetType() == NIL ) {
        walk->m_right = NULL ;
        walk = NULL ;
      } // else if
      else {
        walk->m_right = GetBinding( walk->m_right, getAddress ) ;
        if ( walk->m_right->m_key.GetType() == NIL )
          walk->m_right = NULL ;
        walk = NULL ;
      } // else
    } // while

 
    return head ;
  } // UnFoldTree()

  bool Is_Equal_Tree( Tree * tree_1, Tree * tree_2 ) {
    // for ( equal? ) function
    NodeType compare_1_Type, compare_2_Type ;
    string compare_1_Key, compare_2_Key ;

    bool interrupt = false ;
      
    if ( tree_1 == NULL || tree_2 == NULL ) {
      if ( tree_1 == NULL && tree_2 == NULL ) 
        return false ;
      else {
        if ( tree_1 == NULL ) {
          if ( tree_2->m_key.GetType() == NIL )
            return false ;
          else 
            return true ;
        } // if
        else if ( tree_2 == NULL ) {
          if ( tree_1->m_key.GetType() == NIL )
            return false ;
          else 
            return true ;
        } // else if
      } // else
    } // if


    // middle 
    compare_1_Type = tree_1->m_key.GetType() ;
    compare_1_Key = tree_1->m_key.GetKey() ;
    compare_2_Type = tree_2->m_key.GetType() ;
    compare_2_Key = tree_2->m_key.GetKey() ;

    if ( compare_1_Key == compare_2_Key && compare_1_Type == compare_2_Type ) {
      
      if ( Is_Equal_Tree( tree_1->m_left, tree_2->m_left ) ) 
        interrupt = true ;
      
      if ( Is_Equal_Tree( tree_1->m_right, tree_2->m_right ) ) 
        interrupt = true ;
    } // if
    else 
      interrupt = true ;

    return interrupt ;
  } // Is_Equal_Tree()

  bool Check_COND_FORMAT( Tree * head ) {
    // for COND function type checking
    bool check = true ;
    bool have_dot = false ;
    head = head->m_right ;
    while ( head != NULL && check ) {
      if ( head->m_left->m_key.GetType() != INTERNAL_NODE ) 
        check = false ;
      else {
        if ( Count_arguments( head->m_left, have_dot ) <= 1 ) 
          check = false ;
        else if ( have_dot ) 
          check = false ;
      } // else if

      head = head->m_right ;
    } // while

    return check ;
  } // Check_COND_FORMAT()

  KeyDefine Arithmetic_operator( string operate_type, KeyDefine key1, KeyDefine key2 ) {
    bool have_float = false ;
    int result_int ;
    float result_float ;
    if ( key1.GetType() == FLOAT || key2.GetType() == FLOAT ) 
      have_float = true ;

    if ( have_float ) {

      if ( key1.GetType() == INT )                               // key1
        result_float = String_to_Int( key1.GetKey() ) ;
      else if ( key1.GetType() == FLOAT ) 
        result_float = String_To_Float( key1.GetKey() ) ;

                                                                  // key2
      if ( operate_type == "+" ) {
        if ( key2.GetType() == INT )
          result_float = result_float + String_to_Int( key2.GetKey() ) ;
        else if ( key2.GetType() == FLOAT ) 
          result_float = result_float + String_To_Float( key2.GetKey() ) ;
      } // if
      else if ( operate_type == "-" ) {
        if ( key2.GetType() == INT )
          result_float = result_float - String_to_Int( key2.GetKey() ) ;
        else if ( key2.GetType() == FLOAT ) 
          result_float = result_float - String_To_Float( key2.GetKey() ) ;
      } // else if
      else if ( operate_type == "*" ) {
        if ( key2.GetType() == INT )
          result_float = result_float * String_to_Int( key2.GetKey() ) ;
        else if ( key2.GetType() == FLOAT ) 
          result_float = result_float * String_To_Float( key2.GetKey() ) ; 
      } // else if
      else if ( operate_type == "/" ) {
        if ( Is_Zero( key2.GetKey() ) ) {
          cout << "ERROR (division by zero) : /" << endl ;
          throw 4 ;
        } // if
        else {
          if ( key2.GetType() == INT )
            result_float = result_float / String_to_Int( key2.GetKey() ) ;
          else if ( key2.GetType() == FLOAT ) 
            result_float = result_float / String_To_Float( key2.GetKey() ) ;
        } // else
      } // else if
    } // if

    else {
      result_int = String_to_Int( key1.GetKey() ) ;
                                                                  // key2
      if ( operate_type == "+" ) {
        result_int = result_int + String_to_Int( key2.GetKey() ) ;
      } // if
      else if ( operate_type == "-" ) {
        result_int = result_int - String_to_Int( key2.GetKey() ) ;
      } // else if
      else if ( operate_type == "*" ) {
        result_int = result_int * String_to_Int( key2.GetKey() ) ;
      } // else if
      else if ( operate_type == "/" ) {
        if ( Is_Zero( key2.GetKey() ) ) {
          cout << "ERROR (division by zero) : /" << endl ;
          throw 4 ;
        } // if
        else {
          result_int = result_int / String_to_Int( key2.GetKey() ) ;
        } // else
      } // else if
    } // else
      

    KeyDefine store( NONE, "default", 0, 0 ) ; 
    if ( have_float ) {
      store.SetType( FLOAT ) ;
      store.SetKey( Float_to_String( result_float ) ) ;
    } // if
    else {
      store.SetType( INT ) ;
      store.SetKey( Int_to_String( result_int ) ) ;
    } // else


    return store ;
  } // Arithmetic_operator()

  bool CompareKey( string type, KeyDefine keydefine_1, KeyDefine keydefine_2 ) {
    string key1 = keydefine_1.GetKey() ;
    string key2 = keydefine_2.GetKey() ;

    float key1_convert, key2_convert ;
    if ( keydefine_1.GetType() == INT ) 
      key1_convert = String_to_Int( keydefine_1.GetKey() ) ;
    else if ( keydefine_1.GetType() == FLOAT ) 
      key1_convert = String_To_Float( keydefine_1.GetKey() ) ;
    
    if ( keydefine_2.GetType() == INT ) 
      key2_convert = String_to_Int( keydefine_2.GetKey() ) ;
    else if ( keydefine_2.GetType() == FLOAT ) 
      key2_convert = String_To_Float( keydefine_2.GetKey() ) ;



    if  ( type == ">" ) {
      if ( key1_convert > key2_convert ) 
        return true ;
      else 
        return false ;
    } // if
    else if ( type == ">=" ) {
      if ( key1_convert >= key2_convert ) 
        return true ;
      else 
        return false ;
    } // else if
    else if ( type == "<" ) {
      if ( key1_convert < key2_convert ) 
        return true ;
      else 
        return false ;
    } // else if  
    else if ( type == "<=" ) { 
      if ( key1_convert <= key2_convert ) 
        return true ;
      else 
        return false ;
    } // else if
    else if ( type == "=" ) {
      if ( key1_convert == key2_convert ) 
        return true ;
      else 
        return false ;
    } // else if
    else if ( type == "string>?" ) {
      // key1.erase( key1.begin() ) ;
      // key1.erase( key1.end() - 1 ) ;
      // key2.erase( key2.begin() ) ;
      // key2.erase( key2.end() - 1 ) ;
      if ( key1 > key2 ) 
        return true ;
      else
        return false ;
    } // else if
    else if ( type == "string<?" ) {
      // key1.erase( key1.begin() ) ;
      // key1.erase( key1.end() - 1 ) ;
      // key2.erase( key2.begin() ) ;
      // key2.erase( key2.end() - 1 ) ;
      if ( key1 < key2 ) 
        return true ;
      else
        return false ;
    } // else if
    else if ( type == "string=?" ) {
      // key1.erase( key1.begin() ) ;
      // key1.erase( key1.end() - 1 ) ;
      // key2.erase( key2.begin() ) ;
      // key2.erase( key2.end() - 1 ) ;

      if ( key1 == key2 ) 
        return true ;
      else
        return false ;
    } // else if
    else 
      cout << "error, CompareKey Wrong Type " << endl ;
    return true ;

  } // CompareKey()



  Tree * Evaluate_Constructors( Tree * tree, string type ) {
    // cons (2)
    // 將前面的成員推入後面的list (若後面非list,則2個成員將組成一個pair) 

    // list (>= 0)
    // 將參數列轉為list 

    try {
      Tree * head = Copy_Tree( tree ) ;
      Tree * evaluate = NULL ;  
      bool have_dot = false ;

      if ( type == "cons" ) {  // (cons a . b)
        int count = Count_arguments( head, have_dot ) - 1 ;

        if ( count != 2 ) {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ;
        } // if

        else {
          head = UnFoldTree( head, false ) ;
          evaluate = new Tree() ;
          evaluate->m_key = KeyDefine( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
          evaluate->m_left = head->m_right->m_left ;
          evaluate->m_right = head->m_right->m_right->m_left ;
        } // else
      } // if
      
      else if ( type == "list" ) {
        int count = Count_arguments( head, have_dot ) - 1 ;
        KeyDefine internalnode( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;

        if ( count == 0 ) {
          evaluate = new Tree() ;
          evaluate->m_key = KeyDefine( NIL, "nil", 0, 0 ) ;
        } // if
        else {
          head = head->m_right ;
          head = UnFoldTree( head, false ) ;
          Tree * walk = evaluate ;
          
          while ( head != NULL ) {
            if ( head->m_left != NULL ) {
              if ( walk == NULL ) {
                evaluate = new Tree() ;
                evaluate->m_key = internalnode ;
                evaluate->m_left = head->m_left ;
                walk = evaluate ;
              } // if
              else {
                walk->m_right = new Tree() ;
                walk->m_right->m_key = internalnode ;
                walk = walk->m_right ;
                walk->m_left = head->m_left ;
              } // else
            } // if

            if ( head->m_right == NULL )
              head = head->m_right ;
            else if ( head->m_right->m_key.GetType() == INTERNAL_NODE ) 
              head = head->m_right ;
      
          } // while          
        } // else

      } // else if


      return evaluate ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Constructors()

  Tree * Evaluate_Quote( Tree * head ) {
    // quote (1)    將list視為資料而不評估它 
    // '     (1)
    try {
      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;

      if ( count != 1 ) {
        cout << "ERROR (incorrect number of arguments) : " << "quote" << endl ;
        throw 4 ;
      } // if
      
      return Label_Keydefine_Proect( head->m_right->m_left ) ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Quote()

  void Evaluate_Define( Tree * head ) {
    // define (2)
    // cannot define keywords
    try {
      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;
      if ( count != 2 ) {
        cout << "ERROR (DEFINE format) : " ;
        g_Result = head ;
        throw 6 ;
      } // if
      else if ( Is_Keywords( head->m_right->m_left->m_key.GetKey() ) ) {
        cout << "ERROR (DEFINE format) : " ;
        g_Result = head ;
        throw 6 ;
      } // else if
      else if ( head->m_right->m_left->m_key.GetType() != SYMBOL ) {
        cout << "ERROR (DEFINE format) : " ;
        g_Result = head ;
        throw 6 ;
      } // else if
      else {
        head->m_right->m_right = UnFoldTree( head->m_right->m_right, true ) ;
  
        InsertDefine( head->m_right->m_left->m_key.GetKey(), head->m_right ) ;
      } // else
    } // try
    catch( int num ) {
      throw num ;
    } // catch

  } // Evaluate_Define()

  Tree * Evaluate_Part_Accessors( Tree * head, string type ) {
    // car (1) (從list之中抓出第一個成員) 
    // cdr (1) (去除第一個成員後的list)  
    try {
        
      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;
      if ( have_dot )  {
        cout << "ERROR (non-list) : " ;
        g_Result = head ;
        throw 6 ;
      } // if
      else if ( count != 1 ) {
        cout << "ERROR (incorrect number of arguments) : " << type << endl ;
        throw 4 ;      
      } // else if

      head = UnFoldTree( head, false ) ;

      if ( head->m_right->m_left->m_key.GetType() != INTERNAL_NODE ) {
        cout << "ERROR (" << type << " with incorrect argument type) : " ;
        g_Result = head->m_right->m_left ;
        throw 7 ;
      } // if
      
      

      Tree * temp = new Tree() ;
      temp->m_key = KeyDefine( NIL, "nil", 0, 0 ) ; 

      if ( type == "car" ) {
        if ( head->m_right->m_left->m_left == NULL ) 
          return temp ;
        else 
          return head->m_right->m_left->m_left ;
      } // if
      else if ( type == "cdr" ) {
        if ( head->m_right->m_left->m_right == NULL )
          return temp ;
        else 
          return head->m_right->m_left->m_right ;
      } // else if

      return NULL ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Part_Accessors()
  
  Tree * Evaluate_is_primitive( Tree * head, string type ) {
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

    try {
      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;

      if ( count != 1 ) {
        cout << "ERROR (incorrect number of arguments) : " << type << endl ;
        throw 4 ;
      } // if

      if ( head->m_right->m_left->m_key.GetType() == INTERNAL_NODE ) 
        head->m_right->m_left = Eval_SExp( head->m_right->m_left ) ;
      else
        head->m_right->m_left = GetBinding( head->m_right->m_left, false ) ;
      // head = UnFoldTree( head, false ) ;

      Tree * result = new Tree() ;
      KeyDefine t( T, "#t", 0, 0 ) ;
      KeyDefine f( NIL, "nil", 0, 0 ) ;
      NodeType nodetype = head->m_right->m_left->m_key.GetType() ;


      if ( type == "atom?" ) {  // ?
        if ( nodetype == SYMBOL || nodetype == INT || nodetype == FLOAT || nodetype == STRING ||
             nodetype == NIL || nodetype == T ) 
          result->m_key = t ;
        else
          result->m_key = f ;
      } // if
      else if ( type == "null?" ) {
        if ( nodetype == NIL ) 
          result->m_key = t ;
        else
          result->m_key = f ;      
      } // else if
      else if ( type == "integer?" ) {
        if ( nodetype == INT ) 
          result->m_key = t ;
        else
          result->m_key = f ;
      } // else if
      else if ( type == "real?" ||  type == "number?" ) {
        if (  nodetype == INT || nodetype == FLOAT ) 
          result->m_key = t ;
        else
          result->m_key = f ;
      } // else if
      else if ( type == "string?" ) {
        if ( nodetype == STRING ) 
          result->m_key = t ;
        else
          result->m_key = f ;
      } // else if
      else if ( type == "boolean?" ) {
        if ( nodetype == NIL || nodetype == T ) 
          result->m_key = t ;
        else
          result->m_key = f ;      
      } // else if
      else if ( type == "symbol?" ) { 
        if ( nodetype == SYMBOL ) 
          result->m_key = t ;
        else
          result->m_key = f ;
      } // else if
      else if ( type == "pair?" ) {
        if ( nodetype != SYMBOL && nodetype != INT && nodetype != FLOAT && nodetype != STRING &&
             nodetype != NIL && nodetype != T ) {
          result->m_key = t ;

        } // if
        else 
          result->m_key = f ;
      } // else if
      else if ( type == "list?" ) {   // ?
        count = Count_arguments( head->m_right->m_left, have_dot )  ;

        if ( have_dot || count == 1 ) 
          result->m_key = f ;
        else 
          result->m_key = t ;
      } // else if

      return result ;
    } // try
    catch ( int num ) {
      throw num ;
    } // catch 
  } // Evaluate_is_primitive()

  Tree * Evaluate_Basic_arithmetic( Tree * head, string type ) {
    try {
      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;

      Tree * evaluate = new Tree() ;
      KeyDefine t( T, "#t", 0, 0 ) ;
      KeyDefine f( NIL, "nil", 0, 0 ) ;
      KeyDefine store = KeyDefine( NONE, "default", 0, 0 ) ; // default
      evaluate->m_key = store ;

      if ( type == "+" || type == "-" || type == "*" || type == "/" ) {
        //          +              -              *              /      (>= 2)

        if ( count < 2 ) {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ;
        } // if
        else {
          head = head->m_right ;
          while ( head != NULL ) {
            if ( head->m_left->m_key.GetType() == INTERNAL_NODE ) 
              head->m_left = Eval_SExp( head->m_left ) ;
            else
              head->m_left = GetBinding( head->m_left, false ) ;

            if ( head->m_left->m_key.GetType() != INT && head->m_left->m_key.GetType() != FLOAT ) {  
              cout << "ERROR (" << type << " with incorrect argument type) : " ;
              g_Result = head->m_left ;
              throw 6 ;    
            } // if            



            if ( evaluate->m_key.GetType() == NONE ) 
              evaluate->m_key = head->m_left->m_key ;
            else 
              evaluate->m_key = Arithmetic_operator( type, evaluate->m_key, head->m_left->m_key ) ;  
            
            if ( head->m_right == NULL ) 
              head = head->m_right ;
            else if ( head->m_right->m_key.GetType() == INTERNAL_NODE ) 
              head = head->m_right ;
            else 
              head = NULL ;
          } // while
        } // else
      } // if

      else if  ( type == ">" || type == ">=" || type == "<" || type == "<=" || type == "=" ||
                 type == "string-append" || type == "string>?" || type == "string<?" || type == "string=?" )
      {
        //                >              >=              <              <=              =      (>= 2)
        //               string-append              string>?              string>?          string=? (>= 2)
        if ( count < 2 ) {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ;
        } // if
        else {
          head = head->m_right ;
          while ( head != NULL ) {
            if ( head->m_left->m_key.GetType() == INTERNAL_NODE ) 
              head->m_left = Eval_SExp( head->m_left ) ;
            else
              head->m_left = GetBinding( head->m_left, false ) ;

            if ( type == "string-append" ) {
              if ( head->m_left->m_key.GetType() != STRING ) {
                cout << "ERROR (" << type << " with incorrect argument type) : " ;
                g_Result = head->m_left ;
                throw 6 ;
              } // if
              else {
                if ( evaluate->m_key.GetType() == NONE ) {
                  evaluate->m_key =  head->m_left->m_key  ;
                } // if
                else {
                  string string_1 = evaluate->m_key.GetKey() ;
                  string string_2 = head->m_left->m_key.GetKey() ;
                  string_1.erase( string_1.end() - 1 ) ;
                  string_2.erase( string_2.begin() ) ;
                  evaluate->m_key.SetKey( string_1 + string_2 ) ;
                } // else 
              } // else
            } // if
            else {
              if  ( type == ">" || type == ">=" || type == "<" || type == "<=" || type == "=" ) {
                if ( head->m_left->m_key.GetType() != INT && head->m_left->m_key.GetType() != FLOAT ) {
                  cout << "ERROR (" << type << " with incorrect argument type) : " ;
                  g_Result = head->m_left ;
                  throw 6 ;
                } // if
              } // if
              else {
                if ( head->m_left->m_key.GetType() != STRING ) {
                  cout << "ERROR (" << type << " with incorrect argument type) : " ;
                  g_Result = head->m_left ;
                  throw 6 ;
                } // if
              } // else

              if ( evaluate->m_key.GetType() == NONE ) {
                evaluate->m_key = t ;
                store = head->m_left->m_key ;
              } // if  
              else {
                if ( ! CompareKey( type, store, head->m_left->m_key ) ) 
                  evaluate->m_key = f ;

                store = head->m_left->m_key ;
              } // else
            } // else

            if ( head->m_right == NULL )   // find next
              head = head->m_right ;
            else if ( head->m_right->m_key.GetType() == INTERNAL_NODE ) 
              head = head->m_right ;
            else 
              head = NULL ;
          } // while
        } // else

      } // else if
      else if ( type == "not" ) {
        //               not    (1)
        if ( have_dot ) {
          cout << "ERROR (non-list) : " ;
          g_Result = head ;
          throw 6 ;
        } // else if
        else if ( count != 1 ) {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ;
        } // else if
        
        head = UnFoldTree( head, false ) ;
        if ( head->m_right->m_left->m_key.GetType() == NIL ) {
          evaluate->m_key = t ;
        } // if
        else {
          evaluate->m_key = f ;
        } // else if
      } // else if
      else if ( type == "and" || type == "or"  ) {
        //               and              or      (>= 2)

 
        if ( count < 2 ) {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ;
        } // else if
        else {
          Tree * walk = head->m_right ;
          while ( walk != NULL ) {
            if ( walk->m_left->m_key.GetType() == INTERNAL_NODE ) 
              walk->m_left = Eval_SExp( walk->m_left ) ;
            else 
              walk->m_left = GetBinding( walk->m_left, false ) ;


            if ( type == "and" ) {
              if ( walk->m_left->m_key.GetType() == NIL )
                return walk->m_left ;
            } // if
            else {
              if ( walk->m_left->m_key.GetType() != NIL ) 
                return walk->m_left ;
            } // else



            if ( walk->m_right == NULL )
              return walk->m_left ;
            else 
              walk = walk->m_right ;
          } // while
        } // else
      } // else if

      return evaluate ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Basic_arithmetic()

  Tree *  Evaluate_Eqivalence_tester( Tree * head, string type ) {
    // eqv?    (2)
    // equal?  (2)
    try {
      Tree * evaluate = NULL ;
      
      // if ( type == "equal?" ) 
      // head = UnFoldTree( head ) ;
      
      KeyDefine t( T, "#t", 0, 0 ) ;
      KeyDefine f( NIL, "nil", 0, 0 ) ;

      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;
      if ( count != 2 ) {
        cout << "ERROR (incorrect number of arguments) : " << type << endl ;
        throw 4 ;
      } // if 
      else if ( have_dot ) {
        cout << "ERROR (non-list) : " ;
        g_Result = head ;
        throw 6 ;
      } // else if
      else {
        if ( type == "equal?" ) 
          head = UnFoldTree( head, false ) ;
        else 
          head = UnFoldTree( head, true ) ;


        evaluate = new Tree() ;
        evaluate->m_key = t ;
        Tree * compare_1 = head->m_right->m_left ;
        Tree * compare_2 = head->m_right->m_right->m_left ;

        if ( type == "eqv?" ) {
          if ( compare_1->m_key.GetType() == INTERNAL_NODE && compare_2->m_key.GetType() == INTERNAL_NODE ) {
            bool check = false ;
            if ( compare_1 != compare_2 ) {
              // cout << "eqv for false! " << endl ;
              evaluate->m_key = f ;
            } // if
            // else {
            //   cout << "eqv for true " << endl ;
            // } // else 
          } // if
          else if ( compare_1->m_key.GetType() != INTERNAL_NODE &&
                    compare_2->m_key.GetType() != INTERNAL_NODE ) {
            if ( compare_1->m_key.GetType() == STRING || compare_2->m_key.GetType() == STRING ) 
              evaluate->m_key = f ;
            else if ( compare_1->m_key.GetKey() != compare_2->m_key.GetKey() ) 
              evaluate->m_key = f ;
          } // else if
          else {
            evaluate->m_key = f ;
          } // else

        } // if

        if ( type == "equal?" ) {
      
          bool check = Is_Equal_Tree( compare_1, compare_2 ) ;

          if ( check ) 
            evaluate->m_key = f ;
        } // if
        
      } // else

      return evaluate ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Eqivalence_tester()

  Tree * Evaluate_Sequencing_and_functional_composition( Tree * head ) {
    // begin   (>= 1)
    try {
      head = UnFoldTree( head, false ) ;

      bool have_dot ;
      int count = Count_arguments( head, have_dot ) - 1 ;
      if ( count < 1 ) {
        cout << "ERROR (incorrect number of arguments) : " << "begin" << endl ;
        throw 4 ;
      } // if 
      else if ( have_dot ) {
        cout << "ERROR (non-list) : " ;
        g_Result = head ;
        throw 6 ;
      } // else if
      else {
        head = head->m_right ;
        while ( head != NULL ) {
          if ( head->m_right == NULL ) 
            return head->m_left ;
          else 
            head = head->m_right ;
        } // while
      } // else

      return NULL ;
    } // try
    catch( int num ) {
      throw num ;
    } // catch
  } // Evaluate_Sequencing_and_functional_composition()

  Tree * Evaluate_Conditionals( Tree * head, string type ) {
    Tree * copy_tree = Copy_Tree( head ) ;
    bool have_dot ;
    int count = Count_arguments( head, have_dot ) - 1 ;
    try {
      if ( type == "if" ) {
        //          if     (2 or 3)
        // copy_tree = UnFoldTree( copy_tree, false ) ;
        if ( have_dot ) {
          cout << "ERROR (non-list) : " ;
          g_Result = head ;
          throw 6 ;
        } // if
        else if ( count == 2 || count == 3 ) {
          Tree * walk = copy_tree->m_right ;

          // if ( walk->m_left->m_key.GetType() == INTERNAL_NODE ) 
          //   walk->m_left = Eval_SExp( walk->m_left ) ;
          // else 
          //   walk->m_left = GetBinding( walk->m_left, false ) ;
          if ( walk->m_left->m_key.GetType() == INTERNAL_NODE ) 
            walk->m_left = Eval_SExp( walk->m_left ) ;
          else 
            walk->m_left = GetBinding( walk->m_left, false ) ;

          if ( walk->m_left->m_key.GetType() != NIL ) {
            if ( walk->m_right->m_left->m_key.GetType() == INTERNAL_NODE ) 
              return Eval_SExp( walk->m_right->m_left ) ;
            else 
              return GetBinding( walk->m_right->m_left, false ) ;

            // return walk->m_right->m_left ;
          } // if
          else if ( walk->m_left->m_key.GetType() == NIL ) {
            if ( count == 2 ) {
              cout << "ERROR (no return value) : " ;
              g_Result = head ;
              throw 6 ;
            } // if
            else {
              if ( walk->m_right->m_right->m_left->m_key.GetType() == INTERNAL_NODE ) 
                return Eval_SExp( walk->m_right->m_right->m_left ) ;
              else
                return GetBinding( walk->m_right->m_right->m_left, false ) ;
            // return walk->m_right->m_right->m_left ;
            } // else 
          } // else if
        } // else if
        else {
          cout << "ERROR (incorrect number of arguments) : " << type << endl ;
          throw 4 ; 
        } // else
      } // if
      else if ( type == "cond" ) {
        //               cond   (>= 1)

        if ( have_dot ) {
          cout << "ERROR (non-list) : " ;
          g_Result = head ;
          throw 6 ;
        } // if
        else if ( count < 1 ) { 
          cout << "ERROR (COND format) : " ;
          g_Result = head ;
          throw 6 ; 
        } // else if
        else if ( ! Check_COND_FORMAT( copy_tree ) ) {
          cout << "ERROR (COND format) : " ;
          g_Result = head ;
          throw 6 ;      
        } // else if
        else {
          // bool check_false = false ;
          Tree * walk = copy_tree->m_right ;

          while ( walk != NULL ) {

            if ( walk->m_right == NULL  ) {
              if ( walk->m_left->m_left->m_key.GetKey() == "else" ) {
                walk->m_left->m_right = UnFoldTree( walk->m_left->m_right, false ) ;
                
                walk = walk->m_left->m_right ;
                // if ( Count_arguments( walk, have_dot ) == 0 ) {
                //   cout << "ERROR (COND format) : " ;
                //   g_Result = head ;
                //   throw 6 ; 
                // } // if
                // else if ( have_dot ) {
                //   cout << "ERROR (non-list) : " ;
                //   g_Result = head ;
                //   throw 6 ;
                // } // else if
                // else {
                while ( walk != NULL ) {
                  if ( walk->m_right == NULL ) {
                    return walk->m_left ;
                  } // if
                  else if ( walk->m_right->m_key.GetType() == INTERNAL_NODE ) {
                    walk = walk->m_right ;
                  } // else if
                  else {
                    cout << "[Line 2195] : May have error " << endl ;
                    return walk->m_left ;
                  } // else
                } // while
                // } // else
                // return walk->m_left->m_right->m_left ;  // -------------------
              } // if
              else {
                if ( walk->m_left->m_left->m_key.GetType() == INTERNAL_NODE )
                  walk->m_left->m_left = Eval_SExp( walk->m_left->m_left ) ;
                else 
                  walk->m_left->m_left = GetBinding( walk->m_left->m_left, false ) ;
                
                if ( walk->m_left->m_left->m_key.GetType() == NIL ) {
                  cout << "ERROR (no return value) : " ;
                  g_Result = head ;
                  throw 6 ; 
                } // if
                // else if ( Count_arguments( walk->m_left->m_right, have_dot ) == 0 ) {
                //   cout << "ERROR (COND format) : " ;
                //   g_Result = head ;
                //   throw 6 ; 
                // } // else if
                // else if ( have_dot ) {
                //   cout << "ERROR (non-list) : " ;
                //   g_Result = head ;
                //   throw 6 ;
                // } // else if
                else {
                  walk->m_left->m_right = UnFoldTree( walk->m_left->m_right, false ) ;
                  
                  
                  
                  walk = walk->m_left->m_right ;
                  while ( walk != NULL ) {
                    if ( walk->m_right == NULL ) {
                      return walk->m_left ;
                    } // if
                    else if ( walk->m_right->m_key.GetType() == INTERNAL_NODE ) {
                      walk = walk->m_right ;
                    } // else if
                    else {
                      cout << "[Line 2195] : May have error " << endl ;
                      return walk->m_left ;
                    } // else
                  } // while
                  
                  
                  // return walk->m_left->m_right->m_left ;  // -------------------
                } // else 
       
              } // else   
            } // if
            else {
              if ( walk->m_left->m_left->m_key.GetType() == INTERNAL_NODE )
                walk->m_left->m_left = Eval_SExp( walk->m_left->m_left ) ;
              else 
                walk->m_left->m_left = GetBinding( walk->m_left->m_left, false ) ;
              

              if ( walk->m_left->m_left->m_key.GetType() != NIL ) {      // error : == T 
                walk->m_left->m_right = UnFoldTree( walk->m_left->m_right, false ) ;


                walk = walk->m_left->m_right ;
                // if ( Count_arguments( walk, have_dot ) == 0 ) {
                //   cout << "ERROR (COND format) : " ;
                //   g_Result = head ;
                //   throw 6 ; 
                // } // if
                // else if ( have_dot ) {
                //   cout << "ERROR (non-list) : " ;
                //   g_Result = head ;
                //   throw 6 ;
                // } // else if
                // else {
                while ( walk != NULL ) {
                  if ( walk->m_right == NULL ) {
                    return walk->m_left ;
                  } // if
                  else if ( walk->m_right->m_key.GetType() == INTERNAL_NODE ) {
                    walk = walk->m_right ;
                  } // else if
                  else {
                    cout << "[Line 2195] : May have error " << endl ;
                    return walk->m_left ;
                  } // else
                } // while                  
                // } // else
              } // if
            } // else

            walk = walk->m_right ;
          } // while
        } // else
      } // else if
    } // try
    catch ( int num ) {
      throw num ;
    } // catch
    
    return NULL ;
  } // Evaluate_Conditionals()

  void Clean_Environment( Tree * head ) {
    // clean-environment   (0)
    // care : ??喲?   
    head = head->m_right ;
    if ( head == NULL ) 
      ;
    else {
      
      if ( head->m_key.GetType() != NIL ) {
        cout << "ERROR (incorrect number of arguments) : " << "clean-environment" << endl ;
        throw 4 ;
      } // if

    } // else



    // for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
    //   delete g_Define_Binding[i] ;
      
    // } // for

    g_Define_Binding.clear() ;
    cout << "environment cleaned" << endl ;

  } // Clean_Environment()





  public:

  Tree * Label_Keydefine_Proect( Tree * tree ) {

    if ( tree->m_key.GetType() != INTERNAL_NODE ) 
      tree->m_key.SetProtect( true ) ;

    if ( tree->m_left != NULL ) 
      tree->m_left = Label_Keydefine_Proect( tree->m_left ) ;
    
    if ( tree->m_right != NULL ) 
      tree->m_right = Label_Keydefine_Proect( tree->m_right ) ;

    return tree ;
  } // Label_Keydefine_Proect()

  Tree * GetDefine( string name, bool getAddress ) {
    for ( int i = 0 ; i < g_Define_Binding.size() ; i++ ) {
      if ( g_Define_Binding.at( i )->m_left->m_key.GetKey() == name ) {
        

        Tree * binding = NULL ;
        if ( getAddress )
          binding = g_Define_Binding.at( i ) ;
        else
          binding = Copy_Tree( g_Define_Binding.at( i ) ) ;

        // if ( binding->m_right->m_left->m_key.GetType() == INTERNAL_NODE )
        //   return Eval_SExp( binding->m_right->m_left ) ; 
        // else {
        //   if ( GetDefine( binding->m_right->m_left->m_key.GetKey(),
        //                   g_Define_Binding, false ) != NULL ) {
        //     return GetDefine( binding->m_right->m_left->m_key.GetKey(),  g_Define_Binding, getAddress );
        //   } // if

        return binding->m_right->m_left ; 
        // } // else

      } // if
    } // for

    return NULL ;
  } // GetDefine()


  Tree * Eval_SExp( Tree * tree ) {
    // int test_num = 1 ;
    
    bool have_dot = false ;
    int count = Count_arguments( tree, have_dot ) - 1 ;

    if ( tree->m_left->m_key.GetType() == INTERNAL_NODE )
      tree->m_left = Eval_SExp( tree->m_left ) ;
    

    string operate_type = tree->m_left->m_key.GetKey() ;  // cget type
    if ( GetDefine( operate_type, false ) != NULL ) {   // Define change
      tree->m_left = GetBinding( tree->m_left, false ) ;
      operate_type = tree->m_left->m_key.GetKey() ;
    } // if

    Tree * result ;

    try {
      if ( have_dot ) {
        cout << "ERROR (non-list) : " ;
        g_Result = tree ;
        throw 6 ;
      } // if
      else if ( operate_type == "cons" || operate_type == "list" ) {
        result = Evaluate_Constructors( tree, operate_type ) ;
      } // if
      else if ( operate_type == "quote" || operate_type == "\'" ) {
        result = Evaluate_Quote( tree ) ;
      } // else if 
      else if ( operate_type == "define" ) {
        Evaluate_Define( tree ) ;
        throw 2 ;         
      } // else if
      else if ( operate_type == "car" || operate_type == "cdr" ) {
        result = Evaluate_Part_Accessors( tree, operate_type ) ;
      } // else if
      else if ( operate_type == "atom?" || operate_type == "pair?" || operate_type == "list?" ||
                operate_type == "null?" || operate_type == "integer?" || operate_type == "real?" ||
                operate_type == "number?" || operate_type == "string?" || operate_type == "boolean?" || 
                operate_type == "symbol?" ) {
        result = Evaluate_is_primitive( tree, operate_type ) ;
      } // else if
      else if ( operate_type == "+" || operate_type == "-" || operate_type == "*" || operate_type == "/" ||
                operate_type == "not" || operate_type == "and" || operate_type == "or" ||
                operate_type == ">" || operate_type == ">=" || operate_type == "<" || operate_type == "<=" ||
                operate_type == "=" || operate_type == "string-append"  || 
                operate_type == "string>?" || operate_type == "string<?" || operate_type == "string=?" ) {
        result = Evaluate_Basic_arithmetic( tree, operate_type ) ;
      } // else if
      else if ( operate_type == "eqv?" || operate_type == "equal?" ) {
        result = Evaluate_Eqivalence_tester( tree, operate_type ) ;    
      } // else if
      else if ( operate_type == "begin" ) {
        result = Evaluate_Sequencing_and_functional_composition( tree ) ;
      } // else if
      else if ( operate_type == "if" || operate_type == "cond" ) {
        result = Evaluate_Conditionals( tree, operate_type ) ;
      } // else if
      else if ( operate_type == "clean-environment" ) {  
        Clean_Environment( tree ) ;
        throw 8 ;
      } // else if
      else if ( operate_type == "exit" ) {
        cout << "ERROR (incorrect number of arguments) : exit" << endl ;
        throw 4 ;
      } // else if
      else if ( tree->m_left->m_key.GetType() == SYMBOL ) {  // && tree->m_right == NULL
        result = GetDefine( tree->m_left->m_key.GetKey(), false ) ;
        
        if ( result == NULL ) {
          cout << "ERROR (unbound symbol) : " << tree->m_left->m_key.GetKey() << endl ;
          throw 4 ;
        } // if
      } // else if
      else {
        cout << "ERROR (attempt to apply non-function) : " ;
        g_Result = tree->m_left ;
        throw 7 ;
      } // else
    } // try

    catch( int num ) {
      
      if ( num == 2 ) // define
        throw 2 ;
      else if ( num == 4 ) 
        throw 4 ;
      else if ( num == 6 )   // error format, print tree.(Protect)
        throw 6 ;
      else if ( num == 7 ) // error format, print tree.  ()
        throw 7 ;
      else if ( num == 8 )     // clean-environment
        throw 8 ;
      else 
        cout << "There have a known error in Eval_SExp()" << endl ;
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
        // head->m_left->m_key.PrintKey( true ) ;
        PrintAtoM( head->m_left->m_key ) ;
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
          // head->m_right->m_key.PrintKey( true ) ;
          PrintAtoM( head->m_right->m_key ) ;
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


  // void ViolatePrint( Tree * head, int count ) {
  //   for ( int i = 1 ; i < count ; i++ ) {
  //     cout << " " ;
  //   } // for

  //   head->m_key.PrintKey( true ) ;

  //   if ( head->m_left != NULL ) {
  //     cout << "left" << endl ;
  //     ViolatePrint( head->m_left, count+1 ) ;
  //   } // if
    
  //   if ( head->m_right != NULL ) {
  //     cout << "right" << endl ;
  //     ViolatePrint( head->m_right, count+1 ) ;
  //   } // if

  //   cout << "end a node" << endl ;
  // } // ViolatePrint()  
  void PrintAtoM( KeyDefine obj ) {


    if ( Is_Keywords( obj.GetKey() ) && ! obj.GetProtect() ) {
      cout << "#<procedure " ;
      obj.PrintKey( false ) ;
      cout << ">" << endl ;
    } // if
    else {
      obj.PrintKey( true ) ;
    } // else  
  } // PrintAtoM()


  void PrintSExp( Tree * result ) {
  // if ( result == NULL ) 
  // cout << "nil" << endl ;
  // else {
    if ( result->m_key.GetType() == INTERNAL_NODE ) {
      cout << "( " ;
      Print( result, 1 ) ;        
      cout << ")" << endl ;  
    } // if
    else {
      // result->m_key.PrintKey( true ) ; 
      PrintAtoM( result->m_key ) ;
    } // else
        
    // } // else
  } // PrintSExp()

} ; // Print_Exp


int main() {

  Read_Exp read_exp ;
  Build_Tree_Exp build_exp ;
  Evaluate_Exp evaluate_exp ;
  Print_Exp print_exp ;


  vector<Tree*> store_result ;
  cout << "Welcome to OurScheme!" << endl ;
  // cout << "\n" ;
  char onechar ;

  if ( MODE )
    cout << "[debug] Please enter a gTestNum :" ;
  cin >> gTestNum ;


  bool bool_true = true ;
  while ( bool_true ) {
    try {
      cout << "\n" ;
      cout << "> " ;
      gLine = 0 ; 
      gColumn = 1 ;
      gDealToken.clear() ;
      gToken.SetType( NONE ) ;
      delete g_Tree ;
      g_Tree = NULL ;

      Tree * result ;
      
      g_Result = NULL ;
 
      
      read_exp.ReadSExp() ;  // if Syntax Error, throw exception
      // if ( gTestNum == 1 ) {
      build_exp.BuildTree_Interfaces( gDealToken ) ;  // buildtree base gDealToken(), if (exit) throw 0
      
      g_Result = evaluate_exp.Eval_SExp( g_Tree ) ;

      print_exp.PrintSExp( g_Result ) ;  // print_tree( base on g_tree)        
      // } // if



      // collect result
      result = g_Result ;
      store_result.push_back( result ) ;


      // cout << endl  ;
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
        // cout << endl ;
        Tree * temp_result = g_Result ;
        store_result.push_back( temp_result ) ;
      } // else if
      else if ( num == 3 ) {  // syntax error + string error
        // cout << endl ;
      } // else if 
      else if ( num == 4 ) {
        if ( MODE )    cout << "Catch exception in evaluation(),   Done!" << endl; 
      } // else if
      else if ( num == 5 ) { // atom

        if ( gDealToken[0].GetType() == SYMBOL ) {
          if ( Is_Keywords( gDealToken[0].GetKey() ) ) {
            print_exp.PrintAtoM( gDealToken[0] ) ;
          } // if
          else {
            Tree * get_atom_binding = evaluate_exp.GetDefine( gDealToken[0].GetKey(), false ) ;
            if ( get_atom_binding == NULL ) {
              // cout << "ERROR (unbound symbol) : " << gDealToken[0].GetKey() << endl ;
              cout << "ERROR (unbound symbol) : " ;
              print_exp.PrintAtoM( gDealToken[0] ) ;
            } // if
            else
              print_exp.PrintSExp( get_atom_binding ) ;                  
          } // else    
        } // if
        else {
          print_exp.PrintAtoM( gDealToken[0] ) ;
        } // else

      } // else if
      else if ( num == 6 ) {  // error, print s_exp, protect
        evaluate_exp.Label_Keydefine_Proect( g_Result ) ;
        print_exp.PrintSExp( g_Result ) ;
      } // else if
      else if ( num == 7 ) {  // error, print s_exp, NOT PROTECT
        print_exp.PrintSExp( g_Result ) ;
      } // else if
      else if ( num == 8 ) {  // environment cleaned

        store_result.clear() ;
        // while ( ! store_result.empty() ) {
        //   delete store_result[0] ;
        //   store_result[0] = NULL ;
        //   store_result.erase( store_result.begin() ) ;
        // } // while

        // store_result.clear() ;
        for ( int i = 0 ; i < store_result.size() ; i++ ) {
          delete store_result[i] ;
          store_result[i] = NULL ;
        } // for
        
        // store_result.clear() ;
      } // else if
      else 
        cout << "There is a known error in main()" << endl ;
    } // catch


    
  } // while
  
  cout << "Thanks for using OurScheme!"  ;
 
} // main()