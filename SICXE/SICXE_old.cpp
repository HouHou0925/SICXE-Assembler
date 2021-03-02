#include<iostream>
#include<fstream>
#include<cstring>
#include <string> 
#include <vector> 
#include<stdlib.h>
#include<ctime>
#include<iomanip>
#include <algorithm>
#include <stdexcept> // std::out_of_range
#define NOT !
#include<math.h>
#include<set>
#include<map>
#include <iomanip>
#include <typeinfo>
#include <sstream>;
#include <cctype>
#include <ctype.h>


using namespace std;
struct alldata
	{
		
	
		int line ;
		string Loc = "";	
		string Sourcestatement = "" ;
		string def = "" ;
		string table1 = "" ;
		string table2 = "" ;
		string table3 = "" ;
		string table4 = "" ;
		string table5 = "" ;  // table5
		string table6 = ""  ;     // table6
		string table7 = "" ;   // table7
		string Objectcode = "" ;	
		string annotation = "" ; //註解 
		string type = "" ;
	};

class Data{
	
	private:
		char op_TAB[59][7] = { "ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP", "COMPF", "COMPR", "DIV", "DIVF", "DIVR",
				"FIX", "FLOAT", "HIO", "J", "JEQ", "JGT", "JLT", "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL", "LDS",
				"LDT", "LDX", "LPS", "UML", "MULF", "MULR", "NORM", "OR", "RD", "RMO", "RSUB", "SHIFTL", "SHIFTR",
				"SIO", "SSK", "STA", "STB", "STCH", "STF", "STI", "STL", "STS", "STSW", "STT", "STX", "SUB", "SUBF",
				"SUBR", "SVC", "TD", "TIO", "TIX", "TIXR", "WD" };
				
		char opCode[59][5] = { "18,3", "58,3", "90,2", "40.3", "B4,2", "28,3", "88,3", "A0,2", "24,3", "64,3", "9C,2", "C4,1", "C0,1", "F4,1", "3C,3",   // OP CODE 和 TYPE 
				"30,3", "34,3", "38,3", "48,3", "00,3", "68,3", "50,3", "70,3", "08,3", "6C,3", "74,3", "04,3", "E0,3", "20,3", "60,3", "98,3", "C8,1",
				"44,3", "D8,3", "AC,2", "4C,3", "A4,2", "A8,2", "F0,1", "EC,3", "0C,3", "78,3", "54,3", "80,3", "D4,3", "14,3", "7C,3", "E8,3", "84,3",
				"10,3", "1C,3", "5C,3", "94,2", "B0,2", "E0,3", "F8,1", "2C,3", "B8,2", "DC,3" };
		
	public:
		
		int  address = 0 ;  // 一開始先設為0
		int line = 0 ; 
		map< string, int > table1 ; 
		map< string, int > table2 ;
		map< string, int > table3 ;
		map< string, int > table4 ;
		map< string, string > opcode ; 
		map< string, string > addresstable;
		map<string,int>::iterator work; 
		
		vector<alldata> data;
		vector<string> table5; 
		vector<string> table6;
		vector<string> table7;
	
			
		
		bool creat_table() 
		{ // 讀檔
				table5.resize(100) ;
				table6.resize(100) ;
				table7.resize(100) ;
          		string filename = "Table";
         		fstream file;
		 	
		 	 	string stemp = "";	
			  	char ctemp ;
			  	int i = 1 ;          // 在table中第幾個 
			  	int name_num = 1 ;   // 檔名上的處理 
		 	
			 while( name_num != 5 )
			 {
				
				stringstream ss;  // int to string
				ss << name_num ;
				string num = ss.str();	
				
					
				filename = filename + num + ".table" ;	
				file.open(filename.c_str());		 	
		  		if( !file.fail() ) {
		  			
		  			while( getline(file,stemp) )
		  			{
		  				transform(stemp.begin(),stemp.end(),stemp.begin(), ::tolower);
		  				if( filename == "Table1.table")
		  					table1.insert(pair<string,int> ( stemp,i ) ) ;
		  				
						else if( filename == "Table2.table" ) 
		  					table2.insert(pair<string,int> ( stemp,i ) ) ;
		  				
						else if( filename == "Table3.table" ) 
		  					table3.insert(pair<string,int> ( stemp,i ) ) ;
		  			
					  	else if( filename == "Table4.table" ) 
		  					table4.insert(pair<string,int> ( stemp,i ) ) ;
						
						i++;  
						
						
		  				
					}
				
		 		 }
		 		 else {
		  			cout << "No such file:" << filename << endl;
		  				file.close();
		  			return false;
		  		}	
		  
		  		
		  		file.close();	 
		  		filename = "Table" ;
		  		name_num ++ ;
		  		i = 1 ;	
		  		
		  	}
			
			for( int i =0 ; i <= 58 ; i++ )
				opcode.insert( pair<string,string>( op_TAB[i], opCode[i] )) ;
		  	return true;
	
		}
		
			void getToken( 	fstream &file, string filename )
		{
			string stemp = "" ; //暫存還沒切完的字串
			string stemp_place ; //暫存要輸出的token type & value 
			string c_temp ; 
			string stemp_before = "" ; //用來存放沒有轉成小寫的原字串 算ascii用的  
			string stemp_instruction;
			bool first = true ;
			bool allocation = false ;
			bool Delimiter_used = false ;
			bool end = false ;
			int total = 0 ; // 存放ascii總合 
			alldata datatemp ;
			string ans ; // 存整串座標位置的 
			char ctemp;
			ofstream outputfile;         // fstream 需要檔案存在才可以使用 
			filename = "OUTPUT" + filename ;
			
			
			outputfile.open( filename.c_str());
			
			try{
			
			
			while( !end ) {
				
				
				stringstream ss; 
        		ctemp = file.peek();
        		if( ctemp == EOF )
        			end = true ;
        		
        		
        		ss << ctemp;
        		ss >> c_temp ;
        		ss.str("");
				ss.clear();
        		
        		
        		work = table4.find(c_temp);
        		
        		
        		if( ctemp == '.' )
        		{
        		
					ss << table4.at(".") ;
					stemp_place = stemp_place + "(4," + ss.str() + ")"  ;	
					allocation = true; 
					first = false ;
					string gabege ; 
        			
					getline(file,gabege) ;
					stemp_instruction = stemp_instruction + gabege  ;
					datatemp.annotation = stemp_instruction;
					ctemp = '\n' ; 
					
					goto stop ;
			
				}
				else if( ctemp == ' ' ||  ctemp == '\t' || ctemp == '\n' || work != table4.end() || end )
				{
	
					if( work == table4.end()  )
					{
						if( ctemp != '\n' )
						stemp_instruction = stemp_instruction + ctemp ;
						file.get() ;
						
					
					}
					else
					{
						Delimiter_used = true ;
					}
					
//					&& work != table4.end()
					
					start: 
					
					if( stemp.empty() && Delimiter_used   )  
					{
						stemp_instruction = stemp_instruction + ctemp ;
						file.get() ;
						stemp = ctemp ;
						Delimiter_used = false ;
						
					} 
					
					
					
					if( stemp != "" )
					{
						if(stemp == "\n" || stemp == "\t" || stemp == " " )
							goto stop ;
						
						
						
						stemp_before = stemp ;
						transform(stemp.begin(),stemp.end(),stemp.begin(), ::tolower);
						
						
						
						work = table1.find( stemp );
						
						
						if( work != table1.end())
						{
							ss << table1.at(stemp) ;
							stemp_place = stemp_place + "(1," + ss.str() + ")";	
							datatemp.table1 = stemp_before ;
							first = false ;
							goto stop ;
						}
						
						work = table2.find( stemp );
						if( work != table2.end())
						{
							
							ss << table2.at(stemp) ;
							
							stemp_place = stemp_place + "(2," + ss.str() + ")";	
							datatemp.table2 = stemp_before ;
							first = false ;
							goto stop ;
						}
						
						work = table3.find( stemp );
						if( work != table3.end() && ctemp != '\'' )
						{
							ss << table3.at(stemp) ;
							stemp_place = stemp_place + "(3," + ss.str() + ")";	
							datatemp.table3 = stemp_before ;
							first = false ;
							goto stop ;
						}
						
						stop1:
						
						work = table4.find( stemp );
						if( work != table4.end())
						{
							ss << table4.at(stemp) ;
							stemp_place = stemp_place + "(4," + ss.str() + ")";	
							first = false ;
							goto stop ;
						}
						
						//到這邊代表不屬於 table1~4 所以建表
					
					
						total = convertToASCII( stemp_before ) ;
					
						if( isdigit( stemp.at(0) ) )
						{
						
							
							total = total % 100 ;
							while( !table6.at(total).empty() && stemp != table6.at(total) )
							{
								total = (total%100) +1  ; //直到有空位 
								
							}
							
							
							
							if( stemp != table6.at(total) )
							{
									
									table6.at(total) = stemp ;
									datatemp.table6 = stemp_before ;
									stringstream temp ;
									temp << total ;
									stemp_place = stemp_place + "(6," + temp.str() + ")";	
									first = false ;
							}
							else
							{		
									
									stringstream temp ;
									datatemp.table6 = stemp_before ;
									temp << total ;							
									stemp_place = stemp_place + "(6," + temp.str() + ")";
									first = false ;
								
							}

						}
						
					
						else if( Delimiter_used )
						{
							first = false ;
							Delimiter_used = false ;
							
							
							if( stemp == "" )
							{
								
								stemp = ctemp ; 
								file.get() ;
								goto stop1 ;

							}
							else   //  stemp內的字串不屬於table 1~4 及判斷是否為 C'字串' 
							{
								
							
								
								if( stemp == "c" && ctemp == '\'' )    // 字串處理 
								{
									ctemp = file.get(); // C'EOF' 讀掉第一個'
									stemp_instruction = stemp_instruction + ctemp ;
									
									stemp_place = stemp_place + "(4,9)";	
									stemp = "" ;
									
									while( file.peek() != '\'' && file.peek() != '\n' ) 
									{
										ctemp = file.get();
										stemp_instruction = stemp_instruction + ctemp ;
										stemp = stemp +  ctemp ;
									}
									
										ctemp = file.get(); // C'EOF' 讀掉第二個'	
									stemp_instruction = stemp_instruction + ctemp ;
								
									
									
									datatemp.table7 = stemp ;
										ctemp = file.get(); // C'EOF' 讀掉第二個'	
									
									total = convertToASCII( stemp ) ;	
									total = total % 100 ;
									while( !table7.at(total).empty() && stemp != table7.at(total)  )
									{
										total = (total%100) +1  ; //直到有空位 
								
									}
									if( stemp != table7.at(total) )
									{
										
										table7.at(total) = stemp ;
										stringstream temp ;
										temp << total ;
							
										stemp_place = stemp_place + "(7," + temp.str() + ")";	
									}	
									else
									{		
									
										stringstream temp ;
										temp << total ;							
										stemp_place = stemp_place + "(7," + temp.str() + ")";
								
									}
										stemp_place = stemp_place + "(4,9)";
							
									
								}
								else if( stemp == "x" && ctemp == '\'' )    // 字串處理 
								{
	
									ctemp = file.get(); // C'EOF' 讀掉第一個'
									
										
									stemp_instruction = stemp_instruction + ctemp ;
									
									stemp_place = stemp_place + "(4,9)";	
									stemp = "" ;
									
									while( file.peek() != '\'' && file.peek() != '\n' ) 
									{
										ctemp = file.get();
											
										stemp_instruction = stemp_instruction + ctemp ;
										stemp = stemp +  ctemp ;
//										system("pause") ;
									
									}
									
									ctemp = file.get(); // C'EOF' 讀掉第二個'	
									stemp_instruction = stemp_instruction + ctemp ;
										
									datatemp.table7 = stemp ;
									ctemp = file.get(); // C'EOF' 讀掉第二個'																		
									
									total = convertToASCII( stemp ) ;	
									total = total % 100 ;
									while( !table6.at(total).empty() && stemp != table6.at(total)  )
									{
										total = (total%100) +1  ; //直到有空位 
								
									}
									if( stemp != table6.at(total) )
									{
										
										table6.at(total) = stemp ;
										stringstream temp ;
										temp << total ;
							
										stemp_place = stemp_place + "(6," + temp.str() + ")";	
									}	
									else
									{		
									
										stringstream temp ;
										temp << total ;							
										stemp_place = stemp_place + "(6," + temp.str() + ")";
								
									}
									stemp_place = stemp_place + "(4,9)";
									
								}
								else
								{
									
									goto stop1 ;  //MOV, 情況 
									
								}
								
								
							}
	
						}
						else
						{
							
							total = total % 100 ;
							datatemp.table5 = stemp_before ;
							while( !table5.at(total).empty() && stemp != table5.at(total)  )
							{
								total = (total%100) +1  ; //直到有空位 
								
							}
							if( stemp != table5.at(total) )
							{
								
									table5.at(total) = stemp ;
									stringstream temp ;
									temp << total ;
									stemp_place = stemp_place + "(5," + temp.str() + ")";	
								
							}
							else
							{		
									
									stringstream temp ;
									temp << total ;							
									stemp_place = stemp_place + "(5," + temp.str() + ")";
								
							}
							
							if( first )
							{
								datatemp.def = stemp_before ;
							}
							
							first = false ;
						
							
							
							
						}

//						cout << total << endl ;
						total = 0 ;

						stop:
				
						if( ctemp == '\n' || end )
						{
							
							
							
							line = line +5 ;
							datatemp.line = line;
							
							
							datatemp.Sourcestatement = stemp_instruction ;
//							cout <<  stemp_instruction << endl ;
//							system("pause") ;
//							cout <<  "1" << datatemp.Sourcestatement << endl ;
							
							if( datatemp.table2 == "START" )
							{
								
						
								
								address = toDec(datatemp.table6) ;
							
								
								datatemp.Loc = datatemp.table6 ;
							}
							
							else if( allocation || datatemp.table2 == "END" )
							{
								allocation = false ;
								
								
								
							}
							
							
							
							else if ( datatemp.table2 == "BYTE" )
							{
								if( datatemp.Sourcestatement.find( "C'",0 ) > 100 )
								{
									
									datatemp.Loc = toHex(address) ;
									address = address+1  ;
									
								}
								else
								{
									
									datatemp.Loc = toHex(address) ;
									address = address+ datatemp.table7.length() ;
									
								}
								
								
								
							}
							else if ( datatemp.table2 == "RESB")
							{
								datatemp.Loc = toHex(address) ;
							
								address = address + atoi( datatemp.table6.c_str() ) ;
							
							}
							else if ( datatemp.table2 == "EQU")
							{
								
//								cout << datatemp.table6  << "aaaaaaaaaaa "<< endl ;
								datatemp.Loc = toHex( atoi( datatemp.table6.c_str()) ) ;
							
								
							
							}
							else if( datatemp.table2 == "RESW" )
							{
								
								datatemp.Loc = toHex(address) ;
								address = address + toDec( datatemp.table6 )*3 ;
							}
							
							else if( datatemp.table2 == "WORD" )
							{
								
								datatemp.Loc = toHex(address) ;
								address = address + 3 ;
							}
							
							
							else
							{
								datatemp.Loc = toHex(address) ;
//								cout << datatemp.table1 << endl  ; 
								string t =  datatemp.table1 ;
								transform(t.begin(),t.end(),t.begin(), ::toupper);		
								datatemp.type = opcode.at( t ) ;
								datatemp.type = datatemp.type.assign(datatemp.type, 3, 1  ) ;
								
								if( datatemp.type == "1" )
									address = address + 1 ;
								else if (  datatemp.type == "2" )
									address = address + 2 ;
								else
								{
									if(datatemp.Sourcestatement.find( "+" ) > 100 )
										address = address + 3 ;
									else
									{
										datatemp.type = "4" ;
										address = address + 4 ;
										
									}
								}
									
								
							
							
							
							
							}
							
							
//							outputfile << stemp_instruction ;
//							outputfile << stemp_place << endl ;
							
							
							if( !datatemp.def.empty()   )
							{
//								cout << "why:" << datatemp.table5 <<endl ;
							    addresstable.insert( pair<string,string>( datatemp.def, datatemp.Loc )) ;
							    
							
							}
							
							
							data.push_back( datatemp ) ;
							alldata k ;
							datatemp = k ; 
							first = true ;
							stemp_instruction = "";
							stemp_place = "" ;	
						}
			
						stemp = "" ;
						ss.str("");
						ss.clear();
	
					}
			
				
					
					
				}
				
				else
				{
					ctemp = file.get() ;
					stemp_instruction = stemp_instruction + ctemp ;
					stemp = stemp + ctemp ;		
				}				
	
   			}
//   				cout << addresstable.at("CLOOP") << endl ;
   		
   			
		}
		catch (exception &anyException)
		{
			
			
			cout << anyException.what() ;
		}
			
			outputfile.close() ;
		}
	
		bool Read_File(string filename)
		{
			fstream file;
			file.open(filename.c_str());	
				 	
		  		if( !file.fail() ) {
		  			
		  		
					getToken( file, filename ) ;
		  			
		  			
		  			return true;
				
		 		 }
		 		 else {
		  			cout << "No such file:" << filename << endl;
		  			return false;
		  		}	

		  	file.close();	 

		}
		
		
		
		void printdata( string filename)
		{	
			filename = "OUTPUT" + filename ;
			ofstream outputfile;         // fstream 需要檔案存在才可以使用 
			outputfile.open( filename.c_str());	
			vector<alldata>::iterator it;
			cout << "Line" << "\t" << 	"Loc" << "\t" << 	"Source statement" << "\t\t" <<  "Object code" << endl << endl ; 
			outputfile << "Line" << "\t" << 	"Loc" << "\t" << 	"Source statement" << "\t\t" <<  "Object code" << endl << endl ;
			string op ;
			
			for(it=data.begin(); it!=data.end(); ++it) 
			{
			
		
//				if( it->table2 =="START"|| it->table2 =="RESW" || it->table2 =="RESB" || it->table2 =="END" || it->table2 =="BYTE" || it->table2 =="EQU" || it->table2 =="WORD" || !it->annotation.empty()   )
//				{
//					if( it->table2 =="BYTE" )  
//					{
//						if( it->Sourcestatement.find( "C'" ) <100 )  // c'' 轉16進位 ascii 
//						{
//							string tempnum ;	
//						  for( int i =0; i< it->table7.length() ; i++ )
//							{
//								tempnum += toHex( (int)it->table7.at(i) );
//								
//							}
//							it->Objectcode = tempnum ;
//						}
//						else
//						{
//							it->Objectcode =  it->table7 ;
//							
//						}
//						
//						
//						
//					}
//					
//					if( it->table2 =="WORD")
//					{
//						string temp = "" ;
////						cout << it->table7 << endl  ;
//						temp = toHex( atoi( it->table6.c_str() ) )  ;
//						for( ;temp.length() < 6 ;)
//							temp = "0"+temp ;
//							
//						it->Objectcode = temp ;	
//					}
//					
//					
//					// 不翻機器碼 
//				}
//				else
//				{
//				
//					string t = it->table1 ;
//					transform(t.begin(),t.end(),t.begin(), ::toupper);
//				
//					if( it->table1 == "RSUB" )
//					{
//						
//						
//						
//						it->Objectcode = t.assign( t , 0 , 2) + "0000" ;
//						it->Sourcestatement += "\t" ;
//					}
//					else
//					{
////						cout << it->table1 << endl ;
//						
//						it->Objectcode = t.assign( t , 0 , 2) + addresstable.at( it->table5 ) ;
//					
//							
//						 if( it->Sourcestatement.find( ",X" ) < 100 )
//						 	it->Objectcode = toHex( toDec(	it->Objectcode ) + 32768 ) ;
//						 	
//					
//						 	
//						 	
//					}
//					
//					
//					
////					cout << it->table1 ;
////					cout << opcode.at("RSUB") ;
////					op = opcode.at( it->table1 ).assign( opcode.at( it->table1 ) , 0 , 2) ;
////					cout << it->table1  << endl ;
//					
//				}
////***************************************以下處理排版*******************************************************************
//				if( it->Sourcestatement.find( ",X" ) < 100 )              
//					it->Sourcestatement += "\t" ;
//				else
//				{
//						it->Sourcestatement += "\t\t" ;
//					}	
				
				cout  << it->line << "\t" << it->Loc  << "\t" << it->Sourcestatement  << it->Objectcode  << endl; 
				outputfile << it->line << "\t" << it->Loc  << "\t" << it->Sourcestatement  << it->Objectcode  << endl; 
			}
				
		}
		
		
//******************************************************************************************************************************************		
		
		int convertToASCII(string letter)
		{
			int temp = 0 ;
    		for (int i = 0; i < letter.length(); i++)
    		{
       			char x = letter.at(i);
        		temp = temp + x ;
    		}
    		return temp ;
		}
		
		
		char DecToHex (unsigned int n)  
		{
    		char hex[] = {'0', '1', '2', '3','4','5'
                 ,'6','7','8','9','A','B','C'
                 ,'D','E','F'
                 };
		    return hex[n] ;
		}
		
		string toHex (int num )  // 10轉16 
    	{
        	unsigned int unNum = (int) num ;
        	string result ;

       		do 
       		{
            	result = DecToHex(unNum % 16) + result ;
            	unNum /= 16 ;
        	} while (unNum>0);
        		return result ;
    	}
    	
    	 int toDec( string str )  //16轉10 
		{
			
      		
     		return strtol( str.c_str(), NULL,16 ) ;
		}
		
		
	
		
		 
	
	
};

int main() {

	Data data ;
	string filename = "" ;
	bool load ;
	ofstream file ;

//
//	string a = "abc" ;
//	cout << a.assign(a, 0, 2) ;

	
	if( data.creat_table() )
	{
//		
			while( true )
			{
				cout << "請輸入檔名(ex:SIC_input.txt)" << endl;
//				cin >> filename;
				filename = "SICXE.txt";
//				filename = "SICXE_input.txt";
				load = data.Read_File(filename);   //pass1
				
				if( load )
					break;
				
		
				
			}
		 
		 
		  	cout << data.opcode.at("LDA") ;
//		 	cout << data.data.at(15).Sourcestatement     ;
//			cout << data.data.at(17).line << "  "  << "A" ;
//			data.printdata( filename );
//			cout << data.data.at(49).line << "  "  << "A" ;


	}
	
//	if( data.opcode.find("ADD") == data.opcode.end() )
//		 	cout << "aa" ;


}


