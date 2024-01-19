/*
    Project1 75 % : GetToken 是Get The Whole Line 版本
    quote 系統尚未運行
*/

# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include <iomanip> 

# define MODE 0  // 0 : info mode
                 // 1 : GetToken  (Line)    
                 // 1 : debug mode 
using namespace std ;

// enum ErrorType { None, EndOfFile, EndOfLine, EscapeError } ;
enum NodeType { INTERNAL_NODE, SEMI, DOT, SINGLE_QUOTE, DOUBLE_QUOTE, SYMBOL, INT, FLOAT, STRING, NIL, T, LEFT_PAREN, RIGHT_PAREN, END_OF_LINE, END_OF_TOKENLIST };



struct KeyDefine {
  NodeType type ; 
  string key ;
  int line ;      // same as gLine (define in below) ;
  int column ;    // same as gColumn (define in below) ;
  
  KeyDefine( NodeType setType, string setKey, int setLine, int setColumn ) {    // constructor()
    type = setType ;
    if ( type == NIL ) 
      key = "nil" ;
    else 
      key = setKey ;
    line = setLine ;
    column = setColumn ;
  } // KeyDefine()   constructor() 
  KeyDefine() {} // constructor()                      
  
  NodeType GetType() {
    return type ;
  } // GetType()

  string GetKey() {
      return key ;
  } // GetKey()

};

struct Tree {
  KeyDefine key ;
  Tree * left = NULL;
  Tree * right = NULL;
  //Tree * parent ;


  //void Interfaces_Print( ) {
  //  if ( )
  //}
};

int gTestNum ;      // PAL special format
//bool gEOF = false ;    // present whether EndOfFile
//bool gEXIT = false ;   // present whether (exit) successfully 
int gLine = 0 ;     // present the vector location    (start from 0 ...)
int gColumn = 0 ;   // present the vector location    (start from 0 ...)
string gSourceCode ;
vector<KeyDefine>gDealToken ;
// string gDealArray ;

// ErrorType gError = None ;
//vector<string>gErrorMessage ;

class Identify {
  public : 

  bool isWhiteSpace(string str) {
    if (str == "\n" || str == "\t" || str == " " )
      return true ;
    else
      return false ;
  } // isWhiteSpace()
  
  bool isSpace(string str) {
    if ( str == " ")
      return true ;
    else
      return false ;
  } // isSpace()

  bool isTab(string str) {
    if ( str == "\t")
      return true ;
    else
      return false ;
  } // isTab()

  bool isEnter(string str) {
    if ( str == "\n") 
      return true ;
    else
      return false ;
  } // isEnter()

  bool isLeftParen(string str) {
      if (str == "(" ) 
        return true ;
      else
        return false ;
  } // isLeftParen()

  bool isRightParen(string str) {
      if ( str == ")" )
        return true ;
      else
        return false ;
  } // isRightParen()  ")"

  bool isDOT(string str) {
      if ( str == "." ) 
        return true ;
      else
        return false ;
  } // isDOT()

  bool isINT(string str) {
      for ( int i = 0 ; i < str.length() ; i++ ) {
        if ( i == 0 ) {
            char ch = str[0] ;
          if ( ch != '+' && ch != '-' && !isdigit(ch) )
            return false ;
        } // if
        else {
          if (!isdigit(str[i]) ) 
            return false ;
        } // else
      } // for

      return true ;
  } // isINT()

  bool isFLOAT(string str) {
      int count_dot = 0 ;
      string tostring ;
      for ( int i = 0 ; i < str.length() ; i++ ) {
        tostring = str[i] ;  
        if ( i == 0 ) {
            char ch = str[0] ;
          if ( ch != '+' && ch != '-' && !isDOT(tostring) && !isdigit(ch) )
            return false ;
        } // if
        else {
          if ( isDOT(tostring) ) 
            count_dot++ ;
          else if (!isdigit(str[i]) ) 
            return false ;
        } // else
      } // for

      if ( count_dot > 1 )
        return false ;
      else 
        return true ;
  } // isFLOAT()

  bool isT(string str) {
    if ( str == "t" || str == "#t" ) 
      return true ;
    else
      return false ;
  } // isT()

  bool isNIL(string str) {
      if ( str == "nil" || str == "#f" ) 
        return true ;
      else
        return false ;
  } // isNIL()

  bool isSemi(string str) {
    for ( int i = 0 ; i < str.size() ; i++ ) {
      if ( str[i] != ';' )
        return false ;
    } // for
    return true ;
  } // isSemi()

  bool isSingleQUOTE(string str) {
    if ( str == "\'")
      return true ;
    else
      return false ;
  } // isSingleQUOTE()

  bool isDoubleQUOTE(string str) {
    if ( str == "\"") 
      return true ;
    else
      return false ;
  } // isDoubleQUOTE()

  bool isSYMBOL(string str) {
      /**
       * Before call this function, should check int() float() quote()
      */
    string tostring ;
    for ( int i = 0 ; i < str.length() ; i++ ) {
      tostring = str[i] ;
      if ( str[i] == '(' || str[i] == ')' || str[i] == '\'' || str[i] == '\"' || isWhiteSpace(tostring)) 
        return false ;
    } // for
  
    return true ;
  } // isSYMBOL()

  bool isEXIT(string str) {
    if ( str == "str" ) 
      return true ;
    else 
      return false ;
  }

  NodeType GetType(string str) {
      if ( isSemi(str) )
        return SEMI ;
      else if ( isLeftParen(str) )
        return LEFT_PAREN ;
      else if ( isRightParen(str) )
        return RIGHT_PAREN ;
      else if ( isDOT(str) ) 
        return DOT ;
      else if ( isT(str) ) 
        return T ;
      else if ( isNIL(str) ) 
        return NIL ;
      else if ( isSingleQUOTE(str) )
        return SINGLE_QUOTE ;
      else if ( isINT(str) ) 
        return INT ;
      else if ( isFLOAT(str) ) 
        return FLOAT ;
      else if ( isSYMBOL(str) ) 
        return SYMBOL ;
      else 
        return STRING ;
  } // GetType

  void Test_GetType(string str) {
    cout << "Original string is :\"" << str << "\"" << endl ;
    cout << "Type is : \"" << GetType(str) << "\"" ;
    //cout << endl << endl << endl << endl << endl ;

    // ---- FLOAT TEST ----
    cout << "FLOAT TEST" << endl ;
    float print_float = stof(str) ;
    // cout  << fixed <<  setprecision(輸出位數)  <<  變數/數字  <<  endl;
    cout << "FLOAT NUMBER IS :" << fixed << setprecision(3)<< print_float << endl << endl << endl << endl << endl ;
  }

  string GetToken(int & line, int & column) { 
    /**
     * GetNextToken()
     */

    int length = gSourceCode.size() ;
    string temp = "" ;
    string onechar ="" ;
    bool exception_escape = false ;
    bool exception_string = false ;
    bool exception_semi = false ;
    line = gLine ;
    column = gColumn ;
    for ( ; gColumn < length ; gColumn++ ) {    // skip white space
      //cout << "[debug] : gColumn is >>" << gColumn << "<<\n" ;
      onechar = gSourceCode.at(gColumn) ;
      if ( ! isWhiteSpace(onechar) )
        break ;
      else 
        column++ ;
    } // for
    if ( gColumn >= length ) {  // if nothing to get 
      // " "  check error
      KeyDefine temp(END_OF_LINE,"END_OF_LINE", line+1, column) ;
      gDealToken.push_back(temp) ;
      return "" ;
    } // if

    for (  ; gColumn < length ; gColumn++ ) {   // Get Token
      onechar = gSourceCode.at(gColumn) ;
     
      if ( exception_semi ) {
        if ( onechar == "\n" ) {
          gColumn++ ;
          KeyDefine temp(END_OF_LINE,"END_OF_LINE", line+1, gColumn) ;
          gDealToken.push_back(temp) ;
          return "" ;
            break ;
        } // if
      } // if
      else if ( isDoubleQUOTE(onechar) ) {
        temp = temp + onechar ;
        exception_string = !exception_string ;
        if ( !exception_string ) {
          gColumn++ ;
        } // if
      } // else if
      else if ( exception_string ) {
        if ( exception_escape ) {
          if ( onechar == "n" ) 
            temp = temp + "\n" ;
          else if ( onechar == "\"" ) 
            temp = temp + "\"" ;
          else if ( onechar == "t" )
            temp = temp + "\t" ;
          else if ( onechar == "\\" ) 
            temp = temp + "\\" ;
          else
            temp = temp + "\\" + onechar ;
          exception_escape = false ; 
        } // if
        else {
          if ( onechar == "\\" ) 
            exception_escape = true ;
          else if ( onechar == "\n" ) {
              string temp_message = "ERROR (no closing quote) : END-OF-LINE encountered at Line " + to_string(gLine+1) + " Column " + to_string(gColumn+1) ;
              gColumn++ ;
              throw temp_message ;
          } // else if
          else 
            temp = temp + onechar ;
        } // else
      } // else if
      else if ( isWhiteSpace(onechar) ) {
        gColumn++ ;
        break ;        
      } // else if
      else if ( isSemi(onechar) ) {  // have some problem with definition
        // temp = temp + onechar ;
        exception_semi = true ;
      } // else if
      else if (  isLeftParen(onechar) || isRightParen(onechar) || isSingleQUOTE(onechar)  ) {
        if ( temp == "" ) {
          temp = temp + onechar ;
          gColumn++ ;
        } // if
        break ;
      } // else if
      else 
        temp = temp + onechar ;
    } // for

    return temp ;
  } // GetToken()

  void Interfaces_GetToken() {   // get command line ( get token ) 
    // need first deal  (exit)
    string a = "" ;
    int line, column ;
    try {
      a = GetToken(line, column) ;
      while(a!= "") {
        //cout << "[debug] : GetToken Get >>" << a << "<<" << endl ; 
        KeyDefine temp(GetType(a), a, line+1, column+1) ;
        gDealToken.push_back(temp) ;
        a = GetToken(line, column) ;
      } // while       
    } // try()
    catch (string errormessage){
      cout << errormessage << endl ;
    } // catch


    if ( MODE ) {
      //cout << "[info] GetToken Successed! " << endl << endl << endl ;
      
      cout << "[debug] Interfaces_GetToken() : " << endl ;
      for ( int i = 0 ; i < gDealToken.size() ; i++ ) {
        cout << gDealToken.at(i).key << "[" << gDealToken.at(i).line << ":" << gDealToken.at(i).column << "]" << "\t\t" ;
      } // for
      cout << endl << endl ;      
    } // if

  } // Interfaces_GetToken()


  bool Parser_atom(vector<KeyDefine> & list) {
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
      reserve.erase(reserve.begin()) ;             
      if ( reserve.front().GetType() == RIGHT_PAREN ) 
        isType = true ;
      else 
        return false ;
    } // else if
    else 
      return false ;
    
    if ( isType ) {
      reserve.erase(reserve.begin()) ;
      list = reserve ;
      return true ;
    } // if
    else 
      cout << "[error] There have a error in atom" << endl ;
  } // Parser_atom

  bool Parser_Sexp(vector<KeyDefine> & list) {
    /**
     * <S-exp> ::= <ATOM> 
     *            | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
     *            | QUOTE <S-exp>
     *
     *  Remark : {} <- 0 or more
     *           [] <- 0 or 1 
    */
   
    vector<KeyDefine> reserve = list ;
    NodeType type = reserve.front().type ;
    if ( Parser_atom(reserve) ) {
      list = reserve ;
      return true ;
    } // if
    else if ( type == LEFT_PAREN ) {
      reserve.erase(reserve.begin()) ;
      if ( !Parser_Sexp(reserve) ) {
        KeyDefine temp = reserve.front() ;
        cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " << temp.line << " Column " << temp.column << " is >>" << temp.key<< "<<" << endl ;
        return false ;
      } // if
      else {
       // cout << "442" << endl ;
        while(Parser_Sexp(reserve) ) {
          ;
        } // while
        if ( reserve.front().GetType() == DOT ) {
          reserve.erase(reserve.begin()) ;
          Parser_Sexp(reserve) ;
        } // if
        if ( reserve.front().GetType() == RIGHT_PAREN ) {
          reserve.erase(reserve.begin()) ;
          list = reserve ;
          return true ;
        } // if
        else {
        //  cout << "456" << endl ;
          KeyDefine temp = reserve.front() ;
          cout << "ERROR (unexpected token) : ')' expected when token at Line " << temp.line << " Column " << temp.column <<" is >>" << temp.GetKey() << "<<" << endl ;
          return false ;
        } // else 
      } // else
    } // else if
    else if ( type == SINGLE_QUOTE ) {
      reserve.erase(reserve.begin()) ;
      if ( !Parser_Sexp(reserve) ) {
        KeyDefine temp = reserve.front() ;
        cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " << temp.line << " Column " << temp.column << " is >>" << temp.GetKey()<< "<<" << endl ;
        return false ;
      } // if
      else {
        list = reserve ;
        return true ;
      } // else 
    } // else if
    else {
      return false ;
    }
      
    throw 999 ;
   
  } // Parser_Sexp() 


  bool Parser_exit(vector<KeyDefine> & list ) {
    int size = list.size() ;
    if ( size == 4 ) {
      if ( list.at(0).type == LEFT_PAREN && list.at(1).key == "exit" && list.at(2).type == RIGHT_PAREN ) 
        return true ;
    } // if

    return false ;
  } // Parser_exit()

  bool Parser_Interface(vector<KeyDefine> list ) {
    if ( MODE ) {
      cout << "[debug] Parser_Interface()  tokenlist buffer" << endl ;
      for ( int i = 0 ; i < list.size() ; i++ ) {
        cout << list.at(i).GetKey() << "\t\t" ;
      } // for
      cout << endl << endl << endl ;      
    } // if



    bool is_Sexp = false ;
    if ( Parser_exit(list) ) {
      throw 0 ;
    } // if 
    else if ( Parser_Sexp(list) ) {
      return true ;
    } // else if
    else {
      // clear the token before the gDealToken's END_OF_LINE
     // cout << "511" << endl ;
      while ( ! gDealToken.empty() ) {
        if ( gDealToken[0].GetType() == END_OF_LINE ) {
          gDealToken.erase(gDealToken.begin()) ;
          break ;
        } // if
        else {
          gDealToken.erase(gDealToken.begin()) ;
        } // else
      } // while
      return false ;
    } // else

  return false ;
    
  } // Parser_Interface()


} ;

class Expression {
  Identify identify ;

  public : 

  void Print( Tree * head, int count, bool is_new ) {
     // is_new 代表要不要印左括號   out = is_new ? print_paren : print_key
    // 只遞迴Internal Node
   
    if ( MODE )
      cout << "[debug] in Print" << endl ;

    if ( is_new ) 
      cout  << setfill(' ') << setw( 2 * count  ) << "( "  ;

    if ( head->left != NULL ) {
      if ( head->left->key.GetType() == INTERNAL_NODE ) 
        Print( head->left, count+1, true) ;
      else {
        if ( head->left->key.GetType() == FLOAT ) {// cout << setfill(' ') << setw(2*(count-1) ) ;
          if ( is_new )
            cout  << fixed << setprecision(3)  << stof(head->left->key.GetKey())  << endl ;
          else 
            cout << setfill(' ') << setw( 2 * count ) << " " << fixed << setprecision(3)  << stof(head->left->key.GetKey())  << endl ;
        } // if
        else {
          if ( is_new )
            cout  << head->left->key.GetKey()  << endl ;
          else 
            cout  << setfill(' ') << setw( 2 * count ) << " " << head->left->key.GetKey() << endl ;
        } // else 
      } // else
    } // if
    

    if ( head->right != NULL ) {
      if ( head->right->key.GetType() == INTERNAL_NODE ) {
        Print( head->right, count, false) ;
      } // if
      else {
        if ( head->right->key.GetType() != NIL ) {
          cout  << setfill(' ') << setw( 2 * count ) << " " << "." << endl ;
          if ( head->right->key.GetType() == FLOAT ) 
            cout  << setfill(' ') << setw( 2 * count ) << " " << fixed << setprecision(3)  << stof(head->right->key.GetKey())  << endl ;
          else 
            cout  << setfill(' ') << setw( 2 * count ) << " " <<  head->right->key.GetKey() << endl ;          
        } // if
      } // else
    } // if

    if ( is_new ) 
      cout  << setfill(' ') << setw( 2 * (count - 1) ) << ")" << endl ;
  
  } // Print()


  vector<KeyDefine> GetTokenList() {   // () 
    if ( gDealToken.size() == 0 )
      throw 1 ;    // gDealToken  done ;
    if ( MODE ) {
      cout << "[debug] Entering GetTokenList() " << endl ;
    } // if

    int count_paren = 0 ;
    int final_line ;
    int final_column ;
    vector<KeyDefine> reserve = gDealToken ;
    vector<KeyDefine> tokenlist ;
    while( !reserve.empty() ) {
      if ( reserve.front().GetType() == END_OF_LINE ) {
        reserve.erase(reserve.begin()) ;
      } // if
      else {
        if ( reserve.front().GetType() == LEFT_PAREN )
          count_paren++ ;
        else if ( reserve.front().GetType() == RIGHT_PAREN )
          count_paren-- ;
        tokenlist.push_back(reserve.front() ) ;
        reserve.erase(reserve.begin()) ;
        final_line = reserve.front().line ;
        final_column = reserve.front().column ;
      } // else
      
      if ( count_paren == 0 && ! tokenlist.empty()) {
        gDealToken = reserve ;
        KeyDefine temp(END_OF_TOKENLIST, "END_OF_TOKENLIST", final_line, final_column ) ;
        tokenlist.push_back(temp) ; 
        return tokenlist ;
      } // if
    } // while
    throw 1 ;
  } // GetTokenList()

  void ReadSExp() {
    char onechar = '\0';
    gSourceCode = "" ;


  
   while (true) {
      if ( scanf( "%c", &onechar) == EOF ) 
        throw 1 ; // EndOfFile
      else {
        gSourceCode = gSourceCode + onechar ;
        if ( onechar == '\n' ) 
          break ;
      } // else
    } // while

    try{
      identify.Interfaces_GetToken() ;
    } // try
    catch (int num ) {
      if ( num == 2 ) 
        throw 2 ;
      else 
        cout << "There have a unknown error in ReadSExp()" << endl ; 
    }
  } // ReadSExp() 

  
  void SeparateTokenchain(vector<KeyDefine> tokenchain, vector<KeyDefine> & left_tokenchain, vector<KeyDefine> & right_tokenchain ) {

    left_tokenchain.clear() ;
    right_tokenchain.clear() ;
    vector<KeyDefine> reserve ;
    int count_paren = 0 ;
    //int temp_count_paren = 0 ;
    bool left = true ;    ///  left_token 成功分類  true : left繼續    false : left 分完
    bool readquote = false ;  
   // bool end_firstquote = false ;

   // type I : () . ()
   // type II : ( ..  ().. . ..)
   // 
    if ( tokenchain.front().GetType() == LEFT_PAREN && tokenchain.back().GetType() == RIGHT_PAREN ) {  // 切最大括號
      bool check = true ;
      for ( int i = 0 ; i < tokenchain.size() ; i++ ) {
        if ( tokenchain.at(i).GetType() == LEFT_PAREN ) 
          count_paren++ ;
        else if ( tokenchain.at(i).GetType() == RIGHT_PAREN ) 
          count_paren-- ;
        if ( count_paren == 0 && i != tokenchain.size()-1 ) {
          check = false ;
          break ;
        } // if
      } // for

      if ( check ) {
        tokenchain.erase(tokenchain.begin() ) ;
        tokenchain.erase(tokenchain.end() ) ;
      } // if
    } // if


    count_paren = 0 ;
    while(!tokenchain.empty()) {
      if ( left ) {
        if ( tokenchain.front().GetType() == LEFT_PAREN ) 
          readquote = true ;

        if ( readquote ) {
          do {
            if ( tokenchain.front().GetType() == LEFT_PAREN ) 
              count_paren++ ;
            else if ( tokenchain.front().GetType() == RIGHT_PAREN ) 
              count_paren-- ;
            
            left_tokenchain.push_back(tokenchain.front() ) ;
            tokenchain.erase(tokenchain.begin() ) ;
          } while(count_paren != 0 ) ;
        } // if
        else {
          left_tokenchain.push_back(tokenchain.front() ) ;
          tokenchain.erase(tokenchain.begin() ) ;
        } // else
        left = false ;
      } // if
      else {
        right_tokenchain.push_back(tokenchain.front() ) ;
        tokenchain.erase(tokenchain.begin() ) ;
      } // else
    } // while


    if ( MODE ) {
      cout << "[debug] Check left_tokenchain       <<<<<<<<<<" << endl ;
      for ( int i = 0 ; i < left_tokenchain.size() ; i++ ) {
        cout << left_tokenchain.at(i).GetKey() << "\t"  ;
      } // for
      cout << endl ;

      cout << "[debug] Check right_tokenchain       >>>>>>>>>>>" << endl ;
      for ( int i = 0 ; i < right_tokenchain.size() ; i++ ) {
        cout << right_tokenchain.at(i).GetKey() << "\t"  ;
      } // for
      cout << endl << endl ;
    } // if

  } // SeparateTokenchain()

  Tree * BuildTree(vector<KeyDefine> tokenchain, bool new_internal) {

    if ( MODE )
      cout << "[debug] in BuildTree()" << endl ; 
    Tree * head = new Tree() ;
    vector<KeyDefine> left_tokenchain ;
    vector<KeyDefine> right_tokenchain ;
    
    
    if ( tokenchain.size() == 1 && !new_internal) {
      head->key = tokenchain.front() ;
      return head ;
    } // if
    else 
      SeparateTokenchain(tokenchain, left_tokenchain, right_tokenchain ) ;

    if ( right_tokenchain.empty() ) {
      KeyDefine temp(INTERNAL_NODE, "INTERNAL_NODE", 0, 0) ;
      head->key = temp ;
      head->left = BuildTree( left_tokenchain, false ) ;
    } // if
    else {
      KeyDefine temp(INTERNAL_NODE, "INTERNAL_NODE", 0, 0) ;
      head->key = temp ;
      head->left = BuildTree(left_tokenchain, false ) ;
      if ( right_tokenchain.front().GetType() == DOT ) {
        right_tokenchain.erase(right_tokenchain.begin()) ;
        head->right = BuildTree(right_tokenchain, false ) ;
      } // if
      else {
        head->right = BuildTree(right_tokenchain, true ) ;
      } // else
    } // else

    return head ;
  } // BuildTree()

  Tree *  BuildTree_Interfaces( vector<KeyDefine> list) {

    if ( MODE ) 
      cout << "[debug] in BuildTree_Interfaces() "  << endl ;
    
    vector<KeyDefine> tokenchain ;
    KeyDefine temp ;


    bool have_left = false ;
    for ( int i = 0 ; i < list.size() ; i++ ) {             // () -> NIL  
      if ( list.at(i).GetType() == END_OF_TOKENLIST ) 
        ;
      else if ( list.at(i).GetType() == LEFT_PAREN ) {
        temp = list.at(i) ;
        have_left = true ;
      } // else if
      else if ( list.at(i).GetType() == RIGHT_PAREN && have_left ) {
  
        temp.type = NIL ;
        temp.key = "nil" ;
        tokenchain.push_back(temp) ;  

        have_left = false ;
      } // else if 
      else {
        if ( have_left ) 
          tokenchain.push_back(temp) ;
      
        tokenchain.push_back(list.at(i)) ;
        have_left = false ;
      } // else
    } // for

    Tree * head = BuildTree( tokenchain, true ) ;  // NEW_INTERNAL
    return head ;

  } // BuildTree_Interfaces

  void PrintSExp() {
    int count_parent ;
    vector<KeyDefine> buffer ;
    Tree * head = new Tree();

    while (true) {
      delete head ;
      try{
        buffer = GetTokenList() ;
        if ( buffer.size() == 2 ) {
          if (buffer.front().GetType() == FLOAT) 
            cout << fixed <<  setprecision(3)  << stof(buffer.front().GetKey())   << endl ;
          else {
            cout << buffer.front().GetKey() << endl ;
          } // else 
        } // if
        else {
          if (identify.Parser_Interface(buffer) ) {
            if ( MODE ) 
              cout << "Syntax Success!" << endl ;
            head = BuildTree_Interfaces(buffer) ;
            Print(head, 1, true) ;
          } // if
          else {
            cout << "Syntax Error!" << endl ;
          } // else    
        } // else

        gDealToken.clear() ;
      } // try
      catch (int num) { 
        if ( num == 0 ) {   // (exit)
          throw 0 ;
        } // if
        if ( num == 1 ) 
          break ;     // tokenlist is null || tokenlist's left-paren and right-paren is not equal .
      } // catch
    } // while
    
  } // PrintSExp()

} ;



int main() {
  // Identify a ;
  Expression exp ;
  vector<KeyDefine> keylist ;
  //Tree * head = NULL ;
  cout << "Welcome to OurScheme!" << endl ;
  cout << "\n" ;
  cout << "> " ;
  if ( MODE )
    cout << "--- for debug --- Please enter a gTestNum :" ;
  scanf( "%d", &gTestNum ) ;
  
  
  while( true ) {
         // not deal perfectly

      try {
        gLine = 0 ; 
        gColumn = 0 ;
        gSourceCode = "" ;
        exp.ReadSExp() ;
        exp.PrintSExp() ;
      } // try
      catch(int num) {
        if ( num == 0 ) {    // (exit)
          break ;
        } // if
        else if ( num == 1 ) {    // EndOfFile
          cout << "ERROR (no more input) : END-OF-FILE encountered" << endl ;
          break ; 
        } // if
        else if ( num == 2 ) {  // have error in ReadSExp()
          ;
        } // else if 
      } // catch
      cout << "> " ;    // Format Error !
  } // while

  cout << "Thanks for using OurScheme!" << endl ;
 

//system("pause") ;

 
}