# include <stdio.h>
# include <string>
# include <vector>
# include <iostream>
# include <iomanip> 

# define MODE 0
/*
    GetToken殘值
	Error Detect  (clear the line)
	quote
	- new one 概念 
*/ 

using namespace std ;

// END_OF_LINE
enum NodeType { INTERNAL_NODE, SEMI, DOT, SINGLE_QUOTE, DOUBLE_QUOTE, SYMBOL, INT, FLOAT, STRING, NIL, T, 
              LEFT_PAREN, RIGHT_PAREN, END_OF_TOKENLIST 
} ; 

char Int_To_Char( int i ) {
  if ( i == 0 )
    return '0' ;
  else if ( i == 1 )
    return '1' ;
  else if ( i == 2 )
    return '2' ;
  else if ( i == 3 )
    return '3' ;
  else if ( i == 4 )
    return '4' ;
  else if ( i == 5 )
    return '5' ;
  else if ( i == 6 )
    return '6' ;
  else if ( i == 7 )
    return '7' ;
  else if ( i == 8 )
    return '8' ;
  else if ( i == 9 )
    return '9' ;
  return '0' ;
} // Int_To_Char()

int Char_To_Int( char ch ) {
  if ( ch == '0' )
    return 0 ;
  else if ( ch == '1' )
    return 1 ;
  else if ( ch == '2' )
    return 2 ;
  else if ( ch == '3' )
    return 3 ;
  else if ( ch == '4' )
    return 4 ;
  else if ( ch == '5' )
    return 5 ;
  else if ( ch == '6' )
    return 6 ;
  else if ( ch == '7' )
    return 7 ;
  else if ( ch == '8' )
    return 8 ;
  else if ( ch == '9' )
    return 9 ;
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
    // cout << "KeyDefine " << setLine << setColumn << endl ;
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
    if ( m_type == INTERNAL_NODE ) cout << "INTERNAL_NODE" ;
    else if ( m_type == SEMI ) cout << "SEMI" ;
    else if ( m_type == DOT ) cout << "DOT" ;
    else if ( m_type == SINGLE_QUOTE ) cout << "SINGLE_QUOTE" ;
    else if ( m_type == DOUBLE_QUOTE ) cout << "DOUBLE_QUOTE" ;
    else if ( m_type == SYMBOL ) cout << "SYMBOL" ;
    else if ( m_type == INT ) cout << "INT" ;
    else if ( m_type == FLOAT ) cout << "FLOAT" ;
    else if ( m_type == STRING ) cout << "STRING" ;
    else if ( m_type == NIL ) cout << "NIL" ;
    else if ( m_type == T ) cout << "T" ;
    else if ( m_type == LEFT_PAREN ) cout << "LEFT_PAREN" ;
    else if ( m_type == RIGHT_PAREN ) cout << "RIGHT_PAREN" ;
    else if ( m_type == END_OF_TOKENLIST ) cout << "END_OF_TOKENLIST" ;
    else cout << "UnKnown Type in PrintType()" ;

    if ( end_line ) 
      cout << endl ;
  } // PrintType()

  void PrintKey( bool end_line ) {
    if ( m_type == INTERNAL_NODE ) cout << "(key)INTERNAL_NODE" ;
    else if ( m_type == SEMI ) cout << "(key)SEMI" ;
    else if ( m_type == DOT ) cout << m_key ;
    else if ( m_type == SINGLE_QUOTE ) cout << m_key ;
    else if ( m_type == DOUBLE_QUOTE ) cout << m_key ;
    else if ( m_type == SYMBOL ) cout << m_key ;
    else if ( m_type == INT ) cout << m_key ;
    else if ( m_type == FLOAT ) printf( "%.3f", String_To_Float( m_key ) ) ;
    else if ( m_type == STRING ) cout << m_key ;
    else if ( m_type == NIL ) cout << "nil" ;
    else if ( m_type == T ) cout << "#t" ;
    else if ( m_type == LEFT_PAREN ) cout << "(" ;
    else if ( m_type == RIGHT_PAREN ) cout << ")" ;
    else if ( m_type == END_OF_TOKENLIST ) cout << "END_OF_TOKENLIST" ;
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
vector<KeyDefine>gDealToken ;


// string gSourceCode = "" ; // old code 
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

  bool IsLeftParen( string str ) {
    if ( str == "(" ) 
      return true ;
    else
      return false ;
  } // IsLeftParen()

  bool IsRightParen( string str ) {
    if ( str == ")" )
      return true ;
    else
      return false ;
  } // IsRightParen()  ")"

  bool IsDOT( string str ) {
    if ( str == "." ) 
      return true ;
    else
      return false ;
  } // IsDOT()

  bool IsINT( string str ) {
    for ( int i = 0 ; i < str.length() ; i++ ) {
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

    return true ;
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
    if ( str == "t" || str == "#t" ) 
      return true ;
    else
      return false ;
  } // IsT()

  bool IsNIL( string str ) {
    if ( str == "nil" || str == "#f" ) 
      return true ;
    else
      return false ;
  } // IsNIL()

  bool IsSemi( string str ) {
    if ( str.at( 0 ) == ';' ) 
      return true ;
    return false ;
  } // IsSemi()

  bool IsSingleQUOTE( string str ) {
    if ( str == "\'" )
      return true ;
    else
      return false ;
  } // IsSingleQUOTE()

  bool IsDoubleQUOTE( string str ) {
    if ( str == "\"" ) 
      return true ;
    else
      return false ;
  } // IsDoubleQUOTE()

  bool IsBackSlash( string str ) {
    if ( str == "\\" ) 
      return true ;
    else 
      return false ;
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
    if ( str == "str" ) 
      return true ;
    else 
      return false ;
  } // IsEXIT()

  NodeType GetType( string str ) {
    if ( IsSemi( str ) )
      return SEMI ;
    else if ( IsLeftParen( str ) )
      return LEFT_PAREN ;
    else if ( IsRightParen( str ) )
      return RIGHT_PAREN ;
    else if ( IsDOT( str ) ) 
      return DOT ;
    else if ( IsT( str ) ) 
      return T ;
    else if ( IsNIL( str ) ) 
      return NIL ;
    else if ( IsSingleQUOTE( str ) )
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

  void CheckParen() {
    // debug!! 
    int count = 0 ;
    for ( int i = 0 ; i < gDealToken.size() ; i++ ) {
      if ( gDealToken.at( i ).GetType() == LEFT_PAREN ) 
        count++ ;
      else if ( gDealToken.at( i ).GetType() == RIGHT_PAREN ) 
        count-- ;
    } // for

    if ( count <= 0 ) {
      for ( int i = gDealToken.size() - 1 ; i >= 0 ; i-- ) {
        if ( gDealToken.at( i ).GetType() == SEMI ) 
          gDealToken.erase( gDealToken.begin() + i ) ;
      } // for

      KeyDefine temp ( END_OF_TOKENLIST, "END_OF_TOKENLIST", 0, 0 ) ;
      gDealToken.push_back( temp ) ;
      throw 0 ;
    } // if
  } // CheckParen() 

  KeyDefine GetToken() { 

    string getString = "" ;
    string chartoString ; 
    bool exception_escape = false ;
    bool exception_string = false ;
    bool exception_semi = false ;
    int store_line = 0 ;
    int store_column = 0 ;
    bool bool_true = true ;


    if ( gGetChar != '\0' ) {
      if ( MODE ) {
        cout << "[debug] GetToken() : deal multi token ! " << endl ;
      } // if

      getString = gGetChar ;
      store_line = gLine ;
      store_column = gColumn ;
      gGetChar = '\0' ;
      gColumn++ ;
    } // if
    else {
      while ( bool_true ) {
  
        if ( scanf( "%c", &gGetChar ) == EOF ) {
          throw 1 ;
        } // if 
        else {
          chartoString = gGetChar ;
          /*
          cout << "[debug]" << gLine << " " << gColumn << endl ;
          cout << "gGetChar is >>>" ;
          cout << gGetChar ;
          cout << "<<<" << endl ;
          */

          if ( exception_semi ) {
            gGetChar = '\0' ;
            getString = getString + chartoString ;
            if ( chartoString == "\n" ) {
              gLine++ ;
              gColumn = 1 ;
              bool_true = false  ;
            } // if
            else 
              gColumn++ ;
          } // if
          else if ( exception_string ) {
            gGetChar = '\0' ;
            // getString = getString + chartoString ;
            if ( chartoString == "\n" ) {
              cout << "ERROR (no closing quote) : END-OF-LINE encountered at Line " 
              + Int_To_String( gLine ) + " Column " + Int_To_String( gColumn ) << endl ;

              throw 2 ;
            } // if
            
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
            gGetChar = '\0' ;

            if ( getString != "" )  
              bool_true = false ;

            if ( chartoString == "\n" ) {
              gLine++ ;
              gColumn = 1 ;
            } // if
            else 
              gColumn++ ;              

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
              getString = getString + chartoString ;
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
        } // else
      } // while 
    } // else

    KeyDefine temp( GetType( getString ), getString, store_line, store_column ) ; 

    return temp ;

  } // GetToken()


  bool Parser_atom( vector<KeyDefine> & list ) {
  /**
   * have no exception in this function !
    * <ATOM> ::= SYMBOL
    *           | INT 
    *           | FLOAT 
    *           | STRING
    *           | NIL 
    *           | T 
    *           | LEFT-PAREN RIGHT-PAREN 
  */
    vector<KeyDefine> reserve = list;
    NodeType type = reserve.front().GetType() ;
    bool isType = false ;
    if ( type == SYMBOL ) 
      isType = true ;
    else if ( type == INT )
      isType = true ;
    else if ( type == FLOAT ) 
      isType = true ;
    else if ( type == STRING ) 
      isType = true ;
    else if ( type == NIL ) 
      isType = true ;
    else if ( type == T ) 
      isType = true ;
    else if ( type == LEFT_PAREN ) {
      if ( reserve.size() == 1 ) 
        return false ;
      reserve.erase( reserve.begin() ) ;             
      if ( reserve.front().GetType() == RIGHT_PAREN ) 
        isType = true ;
      else 
        return false ;
    } // else if
    else 
      return false ;
    
    if ( isType ) {
      reserve.erase( reserve.begin() ) ;
      list = reserve ;
      return true ;
    } // if
    else 
      cout << "[error] There have a error in atom" << endl ;
    return false ;
  } // Parser_atom()

  bool Parser_Sexp( vector<KeyDefine> & list ) {
  /**
    * <S-exp> ::= <ATOM> 
    *            | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
    *            | QUOTE <S-exp>
    *
    *  Remark : {} <- 0 or more
    *           [] <- 0 or 1 
  */
    
    vector<KeyDefine> reserve = list ;
    KeyDefine temp = reserve.front() ;
    NodeType type = temp.GetType() ;
    reserve.erase( reserve.begin() ) ;   // erase    

    bool check_Syntax_Sexp ;

  
    if ( type == LEFT_PAREN ) {
      if ( Parser_atom( list ) ) 
        return true ;
      
      check_Syntax_Sexp = false ;
      if ( Parser_Sexp( reserve ) ) {
        temp = reserve.front() ;
        while ( temp.GetType() != DOT && temp.GetType() != RIGHT_PAREN ) {
          if ( ! Parser_Sexp( reserve ) ) 
            return false ;
          temp = reserve.front() ;
        } // while

        if ( temp.GetType() == DOT ) {
          reserve.erase( reserve.begin() ) ;
          if ( ! Parser_Sexp( reserve ) ) 
            return false ;
        } // if

        if ( reserve.front().GetType() == RIGHT_PAREN ) {
          reserve.erase( reserve.begin() ) ;
          list = reserve ;
          return true ;
        } // if
        else {
          temp = reserve.front() ;
          cout << "ERROR (unexpected token) : ')' expected when token at Line " 
                << temp.GetLine() << " Column " << temp.GetColumn() << " is >>" 
                << temp.GetKey() << "<<" << endl ;
          return false ;
        } // else 
      } // if
      else {
        // temp = reserve.front() ;
        // cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " 
        //     << temp.GetLine() << " Column " << temp.GetColumn() << " is >>" 
        //     << temp.GetKey() << "<<" << endl ;
        return false ;
      } // else
    } // if
    else if ( type == SINGLE_QUOTE ) {
      if ( Parser_Sexp( reserve ) ) {
        list = reserve ;
        return true ;
      } // if
      else {
        KeyDefine temp = reserve.front() ;
        cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " 
        << temp.GetLine() << " Column " << temp.GetColumn() << " is >>" << temp.GetKey() << "<<" << endl ;
        return false ;
      } // else 
    } // else if
    else if ( Parser_atom( list ) ) {
      return true ;
    } // if
    else {
      cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " 
           << temp.GetLine() << " Column " << temp.GetColumn() << " is >>" 
           << temp.GetKey() << "<<" << endl ;
      return false ;
    } // else 

    return false ;
    
      
    throw 999 ;
   
  } // Parser_Sexp() 


  bool Parser_exit( vector<KeyDefine> & list ) {
    int size = list.size() ;
    if ( size == 4 ) {
      if ( list.at( 0 ).GetType() == LEFT_PAREN && list.at( 1 ).GetKey() == "exit" && 
           list.at( 2 ).GetType() == RIGHT_PAREN ) 
        return true ;
    } // if

    return false ;
  } // Parser_exit()

  bool Parser_Interface( vector<KeyDefine> reserve ) {
  /**
  // <S-exp> ::= <ATOM> 
  //         | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
  //         | QUOTE <S-exp>

  // <ATOM>  ::= SYMBOL | INT | FLOAT | STRING 
  //         | NIL | T | LEFT-PAREN RIGHT-PAREN
  */
    if ( MODE ) {
      cout << "[debug] Parser_Interface()  reserve " << endl ;
      for ( int i = 0 ; i < reserve.size() ; i++ ) {
        reserve.at( i ).PrintKey( false ) ;
        cout << "\t" ;
      } // for

      cout << endl << endl << endl ;      
    } // if

    bool is_Sexp = false ;
    if ( Parser_exit( reserve ) ) {
      throw 0 ;
    } // if 
    else if ( Parser_Sexp( reserve ) ) {
      if ( reserve.size() != 1 ) 
        cout << "792 .. ?" << endl ;
      return true ;
    } // else if

    return false ;
  } // Parser_Interface()


} ;

class Expression {
  Identify m_identify ;

  public : 
  void DebugPrint( Tree * head ) {
    head->m_key.PrintKey( true ) ;
    if ( head->m_left != NULL ) 
      DebugPrint( head->m_left ) ;
    else 
      cout << "left is NULL ! " << endl ;

    if ( head->m_right != NULL ) 
      DebugPrint( head->m_right ) ;
    else 
      cout << "right is NULL ! " << endl ;


    cout << "End a Node !" << endl ;
  } // DebugPrint()


  void Print( Tree * head, int count, bool is_new ) {
  // is_new 代表要不要印左括號   out = is_new ? print_paren : print_key
  // 只遞迴Internal Node
   
    

    if ( is_new ) {
      cout << "( "  ;
    } // if
      
    // cout << setfill( ' ' ) << setw( 2 * count  ) << "( "  ;

    if ( head->m_left != NULL ) {
      if ( head->m_left->m_key.GetType() == INTERNAL_NODE ) 
        Print( head->m_left, count+1, true ) ;
      else {
        if ( is_new )
          head->m_left->m_key.PrintKey( true ) ;
        else {
          // cout << setfill( ' ' ) << setw( 2 * count ) << " " ;
          head->m_left->m_key.PrintKey( true ) ;          
        } // else
      } // else
    } // if
    
    if ( head->m_right != NULL ) {
      if ( head->m_right->m_key.GetType() == INTERNAL_NODE ) {
        cout << setfill( ' ' ) << setw( 2 * count ) << " " ; 
        Print( head->m_right, count, false ) ;
      } // if
      else {
        if ( head->m_right->m_key.GetType() != NIL  ) {
          cout << setfill( ' ' ) << setw( 2 * count ) << " " << "." << endl ; 
          cout << setfill( ' ' ) << setw( 2 * count ) << " " ;
          head->m_right->m_key.PrintKey( true ) ;
        } // if
      } // else
    } // if

    if ( is_new ) {
      if ( count == 1 ) 
        cout << ")" << endl ;
      else 
        cout  << setfill( ' ' ) << setw( 2 * ( count - 1 ) ) << " " << ")" << endl ;
    } // if

  } // Print()

  void ReadSExp() { 
    string oneToken ;
    bool bool_true = true ;
    while ( bool_true ) {
      try {
        KeyDefine temp = m_identify.GetToken() ;   // should throw error or pass 
        gDealToken.push_back( temp ) ;

        if ( MODE ) {
          cout << "[debug] GetToken() : " ;
          cout << "[" << temp.GetLine() << ":" << temp.GetColumn() << "]" ;
          temp.PrintType( false ) ;
          cout << "\t" ;
          temp.PrintKey( true ) ;     
        } // if   

        if ( temp.GetType() != SEMI ) {
          // gDealToken.push_back( temp ) ;
          if ( temp.GetType() != SINGLE_QUOTE )
            m_identify.CheckParen() ;           // throw error of 0 
        } // if

         
      } // try
      catch ( int no ) {
        if ( no == 0 )   // paren = 0 , 
          bool_true = false ;
        else if ( no == 1 ) // EOF encounter 
          throw 1 ;
        else if ( no == 2 )   // error
          throw 2 ;   // pass
        else 
          cout << "ReadSExp() have Unknown Error !" << endl ;
      } // catch      
    } // while
  } // ReadSExp() 

  void SeparateTokenchain( vector<KeyDefine> tokenchain, vector<KeyDefine> & left_tokenchain,
                           vector<KeyDefine> & right_tokenchain, bool new_extend ) {

    left_tokenchain.clear() ;
    right_tokenchain.clear() ;
    vector<KeyDefine> reserve ;
    int count_paren = 0 ;
    bool left = true ;    //  left_token 成功分類  true : left繼續    false : left 分完
    bool readquote = false ;  
    // bool end_firstquote = false ;

    // type I : () . ()
    // type II : ( ..  ().. . ..)
    // 
    if ( MODE ) {
      cout << "[debug] Check tokenchain                " ;
      for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
        cout << tokenchain.at( i ).GetKey() << "  "  ;
      } // for

      cout << endl ;
    } // if

    if ( tokenchain.front().GetType() == LEFT_PAREN && tokenchain.back().GetType() == RIGHT_PAREN ) { 
      // 切最大括號
      bool check = false ;
      for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
        if ( tokenchain.at( i ).GetType() == LEFT_PAREN ) 
          count_paren++ ;
        else if ( tokenchain.at( i ).GetType() == RIGHT_PAREN ) 
          count_paren-- ;
        if ( count_paren == 0 && i == tokenchain.size()-1 ) {
          check = true ;
        } // if
      } // for

      if ( check ) {
        tokenchain.erase( tokenchain.begin() ) ;
        tokenchain.erase( tokenchain.end() ) ;
      } // if
    } // if


    count_paren = 0 ;
    while ( ! tokenchain.empty() ) {
      if ( left ) {
        if ( tokenchain.front().GetType() == LEFT_PAREN ) 
          readquote = true ;

        if ( readquote ) {
          do {
            if ( tokenchain.front().GetType() == LEFT_PAREN ) 
              count_paren++ ;
            else if ( tokenchain.front().GetType() == RIGHT_PAREN ) 
              count_paren-- ;
            
            left_tokenchain.push_back( tokenchain.front() ) ;
            tokenchain.erase( tokenchain.begin() ) ;
          } while ( count_paren != 0 ) ;
        } // if
        else {
          left_tokenchain.push_back( tokenchain.front() ) ;
          tokenchain.erase( tokenchain.begin() ) ;
        } // else

        left = false ;
      } // if
      else {
        right_tokenchain.push_back( tokenchain.front() ) ;
        tokenchain.erase( tokenchain.begin() ) ;
      } // else
    } // while


    if ( MODE ) {
      cout << "[debug] Check left_tokenchain        " ;
      for ( int i = 0 ; i < left_tokenchain.size() ; i++ ) {
        cout << left_tokenchain.at( i ).GetKey() << "  "  ;
      } // for

      cout << "\n[debug] Check right_tokenchain        " ;
      for ( int i = 0 ; i < right_tokenchain.size() ; i++ ) {
        cout << right_tokenchain.at( i ).GetKey() << "  "  ;
      } // for

      cout << endl << endl << endl << endl ;
    } // if

  } // SeparateTokenchain()

  Tree * BuildTree( vector<KeyDefine> tokenchain, bool new_extend ) {

    if ( MODE )
      cout << "[debug] in BuildTree()" << endl ; 
    Tree * head = new Tree() ;
    vector<KeyDefine> left_tokenchain ;
    vector<KeyDefine> right_tokenchain ;
    if ( tokenchain.empty() ) 
      return NULL ;
    
    if ( tokenchain.size() == 1 && !new_extend ) {
      head->m_key = tokenchain.front() ;
      return head ;
    } // if
    else 
      SeparateTokenchain( tokenchain, left_tokenchain, right_tokenchain, new_extend ) ;

    // if ( right_tokenchain.empty() ) {
      KeyDefine temp( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
      head->m_key = temp ;
      head->m_left = BuildTree( left_tokenchain, false ) ;
    // } // if
    // else {
      //KeyDefine temp2( INTERNAL_NODE, "INTERNAL_NODE", 0, 0 ) ;
      head->m_key = temp ;
      head->m_left = BuildTree( left_tokenchain, false ) ;
      if ( right_tokenchain.front().GetType() == DOT ) {
        right_tokenchain.erase( right_tokenchain.begin() ) ;
        head->m_right = BuildTree( right_tokenchain, false ) ;
      } // if
      else {
        head->m_right = BuildTree( right_tokenchain, true ) ;
      } // else
    // } // else

    return head ;
  } // BuildTree()

  Tree * BuildTree_Interfaces( vector<KeyDefine> reserve ) {
    
    if ( MODE ) {
      cout << "[debug] Stage3 : BuildTree_Interfaces() "  << endl ;
      for ( int i = 0 ; i < reserve.size() ; i++ ) {
        cout << reserve.at( i ).GetKey() << "  " ;
      } // for

      cout << endl ;
    } // if
    
    vector<KeyDefine> tokenchain ;
    KeyDefine temp ;
    Tree * head ;

    bool have_left = false ;
    for ( int i = 0 ; i < reserve.size() ; i++ ) {             // '('  ')' -> "()"  

      if ( reserve.at( i ).GetType() == END_OF_TOKENLIST ) 
        ;
      else if ( reserve.at( i ).GetType() == LEFT_PAREN ) {
        if ( have_left ) 
          tokenchain.push_back( temp ) ;
        temp = reserve.at( i ) ;
        have_left = true ;
      } // else if
      else {
        if ( have_left ) {
          if ( reserve.at( i ).GetType() == RIGHT_PAREN ) {
            temp.SetType( NIL ) ;
            temp.SetKey( "nil" )  ;
            tokenchain.push_back( temp ) ;  
          } // if
          else {
            tokenchain.push_back( temp ) ;
            tokenchain.push_back( reserve.at( i ) ) ;
          } // else

          have_left = false ;
        } // if
        else 
          tokenchain.push_back( reserve.at( i ) ) ;
      } // else
    } // for

    if ( tokenchain.size() == 1 ) {
      tokenchain.front().PrintKey( true ) ;
      throw 1 ;
    } // if
    else
      head = BuildTree( tokenchain, true ) ;  // NEW_INTERNAL

    return head ;

  } // BuildTree_Interfaces()

  void PrintSExp() {
    vector<KeyDefine> reserve = gDealToken ;
    try {
      if ( m_identify.Parser_Interface( reserve ) ) {
        if ( MODE ) 
          cout << "[debug] Stage2 : Syntax Success!" << endl ;

        Tree * head = BuildTree_Interfaces( reserve ) ;
        if ( MODE )
          cout << "[debug] in Print" << endl ;

        Print( head, 1, true ) ;
        delete head ;
      } // if
    } // try
    catch ( int num ) {
      if ( num == 0 )    // (exit)
        throw 0 ;
      else if ( num == 1 )   // only one token  
        ;
      else 
        cout << "There has a known error in PrintSExp() " << endl ;
    } // catch
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
  setbuf(stdin, NULL) ; // 使stdin輸入流由預設緩衝區轉為無緩衝區

  cout << "> " ; 
  bool bool_true = true ;

  while ( bool_true ) {
    try {
      gLine = 1 ; 
      gColumn = 1 ;
      gDealToken.clear() ;
      gGetChar = '\0' ;
      if ( MODE ) 
        cout << "------   -------------- ------------ --------------- --------- " << endl ;
      exp.ReadSExp() ;
      if ( MODE ) 
        cout << "[debug] Stage1 : ReadSExp success !" << endl ; 
      exp.PrintSExp() ;

      cout << endl << "> " ;
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
      else if ( num == 2 ) {  // have error in ReadSExp()
        ;
      } // else if 
    } // catch
  } // while
  
  // cout << "\n" ;
  cout << "Thanks for using OurScheme!"  ;
 
} // main()
