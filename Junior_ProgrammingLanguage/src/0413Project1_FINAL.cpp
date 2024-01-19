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
  // 不管精準度

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

string Int_To_String( int i ) {
  string s ;
  while ( i / 10 != 0 ) {
    s = Int_To_Char( i % 10 ) + s;
    i = i / 10 ;
  } // while

  s = Int_To_Char( i % 10 ) + s;
  return s ;
} // Int_To_String() 

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
KeyDefine gToken ;  // remind to give none value 
vector<KeyDefine>gDealToken ;


class Identify {
  public : 

  bool IsDigit( char ch ) {
    if ( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
         ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ) 
      return true ;
    else 
      return false ;
  } // IsDigit() 

  bool IsWhiteSpace( string str ) {
    if ( str == "\n" || str == "\t" || str == " " )     return true ;
    else                                                return false ;
  } // IsWhiteSpace()
  
  bool IsSpace( string str ) {
    if ( str == " " )                                   return true ;
    else                                                return false ;
  } // IsSpace()

  bool IsTab( string str ) {
    if ( str == "\t" )                                  return true ;
    else                                                return false ;
  } // IsTab()

  bool IsEnter( string str ) {
    if ( str == "\n" )                                  return true ;
    else                                                return false ;
  } // IsEnter()

  bool IsLeftParen( string str ) {
    if ( str == "(" )                                   return true ;
    else                                                return false ;
  } // IsLeftParen()

  bool IsRightParen( string str ) {
    if ( str == ")" )                                   return true ;
    else                                                return false ;
  } // IsRightParen()  ")"

  bool IsDOT( string str ) {
    if ( str == "." )                                   return true ;
    else                                                return false ;
  } // IsDOT()

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
        if ( ch != '+' && ch != '-' && !IsDOT( tostring ) && !IsDigit( ch ) )
          return false ;
        else {
          if ( IsDOT( tostring ) ) 
            count_dot++ ;
        } // else 
      } // if
      else {
        if ( IsDOT( tostring ) ) 
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

  bool IsT( string str ) {
    if ( str == "t" || str == "#t" )       return true ;
    else                                   return false ;
  } // IsT()

  bool IsNIL( string str ) {
    if ( str == "nil" || str == "#f" )       return true ;
    else                                     return false ;
  } // IsNIL()

  bool IsSemi( string str ) {
    if ( str.at( 0 ) == ';' )  return true ;
    else                       return false ;
  } // IsSemi()

  bool IsSingleQUOTE( string str ) {
    if ( str == "\'" )      return true ;
    else                    return false ;
  } // IsSingleQUOTE()

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

  bool IsEXIT( string str ) {
    if ( str == "str" )       return true ;
    else                      return false ;
  } // IsEXIT()

  NodeType GetType( string str ) {
    if ( IsSemi( str ) )                  return SEMI ;
    else if ( IsLeftParen( str ) )        return LEFT_PAREN ;
    else if ( IsRightParen( str ) )       return RIGHT_PAREN ;
    else if ( IsDOT( str ) )              return DOT ;
    else if ( IsT( str ) )                return T ;
    else if ( IsNIL( str ) )              return NIL ;
    else if ( IsSingleQUOTE( str ) )      return SINGLE_QUOTE ;
    else if ( IsINT( str ) )              return INT ;
    else if ( IsFLOAT( str ) )            return FLOAT ;
    else if ( IsSYMBOL( str ) )           return SYMBOL ;
    else                                  return STRING ;
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
      else if ( IsLeftParen( chartoString ) || IsRightParen( chartoString ) ) {
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
      else if ( IsSingleQUOTE( chartoString ) ) {
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
      else if ( IsSemi( chartoString ) ) {
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
        if ( num == 1 ) { // EOF
          if ( MODE )  cout << "throw 1 " ;
          throw 1 ;
        } // if
        else if ( num == 2 ) {  // string error 
          if ( MODE )  cout << "throw 2 " ;
          throw 2 ;
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

  void DetectAtoM() {

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

      gDealToken.front().PrintKey( true ) ;
      throw 2 ;
    } // if
  } // DetectAtoM()

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

} ;

class Expression {
  Identify m_identify ;

  public : 

  void PrintSpace( int count ) {
    for ( int i = 0 ; i < 2 * count ; i++ ) {
      cout << " " ; 
    } // for
  } // PrintSpace()

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


  void Print_Function_SingleQuote() {

    Print( g_Tree, 0 ) ;

  } // Print_Function_SingleQuote() 

  void Print_Normal() {
    cout << "( " ;
    Print( g_Tree, 1 ) ;
    cout << ")" << endl ;
  } // Print_Normal()

  void Print( Tree * head, int count ) {
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


  void ReadSExp() {
  
    try {
      m_identify.Parser_Interface() ;    // Should set gDealToken() ;
      if ( MODE ) {
        cout << "[info] Stage1 : ReadSExp success !" << endl ; 
        cout << "   [debug] gDealToken()" ;
        for ( int i = 0 ; i < gDealToken.size() ; i++ ) {
          cout << "[" << gDealToken[i].GetLine() << " " << gDealToken[i].GetColumn() << "]" 
               << gDealToken[i].GetKey() << " " ;
        } // for

        cout << endl ;
      } // if

      m_identify.DetectAtoM() ;  

      BuildTree_Interfaces() ;   // build tree base on gDealToken() ;
      if ( MODE ) 
        cout << "[info] Stage2 : BuildTree success !" << endl ; 

      m_identify.DetectExit() ;
    
    } // try
    catch ( int no ) {
      if ( no == 0 ) // exit
        throw 0 ;
      if ( no == 1 ) // EOF encounter 
        throw 1 ;
      else if ( no == 2 ) // atom
        throw 2 ;
      else if ( no == 3 ) // error
        throw 3 ;
      else 
        cout << " There is a known error in ReadSExp()" << endl ;
    } // catch
  } // ReadSExp() 


  void DEBUG_Print_ITEM( vector< vector<KeyDefine> > item ) {

    cout << "[debug] DEBUG_Print_ITEM() "  << endl ;
    cout << "Print item" << endl ;

    for ( int i = 0 ; i < item.size() ; i++ ) {
      for ( int j = 0 ; j < item[i].size() ; j++ ) {
        cout << item[i][j].GetKey() << " " ;
      } // for

      cout << endl ;
    } // for
  } // DEBUG_Print_ITEM()

  void DEBUG_Print_tokenchain( vector<KeyDefine> tokenchain ) {

    cout << "[debug] DEBUG_Print_tokenchain() "  << endl ;
    cout << "Print tokenchain" << endl ;

    for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
      cout << tokenchain[i].GetKey() << " " ;
    } // for

    cout << endl ;
  } // DEBUG_Print_tokenchain()

  void GetItem( vector<KeyDefine> & tokenchain, vector<KeyDefine> & item ) {
    if ( MODE ) {
      cout << "GetItem() trace" << endl << "  " ;
      for ( int i = 0  ; i < tokenchain.size() ; i++ ) {
        cout << tokenchain[i].GetKey() << " " ;
      } // for

      cout << endl ;
    } // if
      
    bool get_one = false ;
    int count_paren = 0 ;
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

    if ( MODE ) {
      cout << "GetItem() END_trace" << endl << "  " ;
      for ( int i = 0  ; i < tokenchain.size() ; i++ ) {
        cout << tokenchain[i].GetKey() << " " ;
      } // for
      
      cout << endl ;
    } // if

  } // GetItem()

  Tree *  Build_tree_De_Paren( vector <KeyDefine> & tokenchain ) {

    if ( tokenchain.front().GetType() == LEFT_PAREN && tokenchain.back().GetType() == RIGHT_PAREN ) {
      tokenchain.erase( tokenchain.begin() ) ;
      tokenchain.erase( tokenchain.end() ) ;
    } // if

    return BuildTree( tokenchain ) ;
  } // Build_tree_De_Paren()


  Tree * BuildTree( vector<KeyDefine> & tokenchain ) {
    // 只遞迴Internal Node   

    if ( MODE ) {
      cout << "BuildTree() trace" << endl << "  " ;
      for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
        cout << tokenchain[i].GetKey() << " " ;
      } // for

      cout << endl ;
    } // if
      

    Tree * head = new Tree() ;
    KeyDefine internal( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
    head->m_key = internal ;
    vector<KeyDefine> item ;
                         
    GetItem( tokenchain, item ) ;   // item.clear()
    if ( item.size() == 1 ) {                   //  put left-side
      head->m_left = new Tree() ;
      head->m_left->m_key = item.front() ;
      if ( MODE ) {
        cout << "put " << item.front().GetKey() << endl ;
      } // if
    } // if
    else 
      head->m_left = Build_tree_De_Paren( item ) ;      



    if ( ! tokenchain.empty() ) {
      if ( tokenchain.front().GetType() == DOT ) {
        GetItem( tokenchain, item ) ;   // item.clear()  (DOT)
        GetItem( tokenchain, item ) ;   // item.clear()
        if ( item.size() == 1 ) {
          head->m_right = new Tree() ;
          head->m_right->m_key = item.front() ;
        } // if
        else 
          head->m_right = Build_tree_De_Paren( item ) ;
      } // if
      else 
        head->m_right = BuildTree( tokenchain ) ;
    } // if



    return head ;
  } // BuildTree()






  void BuildTree_Interfaces() {
    // build tree base on gDealtoken
    if ( MODE ) {
      cout << "[debug] BuildTree_Interfaces() "  << endl ;
      for ( int i = 0 ; i < gDealToken.size() ; i++ ) {
        cout << gDealToken.at( i ).GetKey() << "  " ;
      } // for

      cout << endl ;
    } // if
    

    if ( gDealToken.front().GetType() == SINGLE_QUOTE ) 
      g_Tree = BuildTree( gDealToken ) ; 
    else 
      g_Tree = Build_tree_De_Paren( gDealToken ) ;

  } // BuildTree_Interfaces()

  void PrintSExp() {
    if ( g_Tree->m_left->m_key.GetType() == SINGLE_QUOTE ) 
      Print_Function_SingleQuote() ;
    else 
      Print_Normal() ;
  } // PrintSExp()

} ;



int main() {
  Expression exp ;
  vector<KeyDefine> keylist ;
  cout << "Welcome to OurScheme!" << endl ;
  cout << "\n" ;
  char onechar ;

  if ( MODE )
    cout << "[debug] Please enter a gTestNum :" ;
  cin >> gTestNum ;
  // setbuf(stdin, NULL) ; //  IDE : Visual Studio Code

  // cout << "> " ; 
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
      if ( MODE ) 
        cout << "------   -------------- ------------ --------------- --------- INIT() ----  " << endl ;
      exp.ReadSExp() ;

      exp.PrintSExp() ;

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
      else if ( num == 2 ) {   // atom
        cout << endl ;
      } // else if
      else if ( num == 3 ) {  
        cout << endl ;
      } // else if 
    } // catch
  } // while
  
  cout << "Thanks for using OurScheme!"  ;
 
} // main()