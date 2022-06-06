#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>



class ITests
{
	public:
	virtual unsigned long run ( int pos  ){}
	
};


class Tester
{
	std::string file1_name;
	std::string file2_name;
	
	std::string path;
	
	std::unique_ptr< ITests > itests;
	
	public:
	
	Tester( const std::string& _path , std::unique_ptr< ITests > _itests ) : path( _path ) , itests( std::move( _itests ) ) {}
	~Tester(){}
	
	void RunTests( void )
	{
		int n = 0;
		
		while( true )
		{
			file1_name = path + (std::string)"/test." + std::to_string( n ) + (std::string)".in";
			file2_name = path + (std::string)"/test." + std::to_string( n ) + (std::string)".out";
			
			
			
			if( !std::filesystem::exists( (std::filesystem::path) file1_name ) || !std::filesystem::exists( (std::filesystem::path) file2_name ) )
			{
				std::cout<<"file not exists!"<<std::endl;
				break;
			}	
			
			RunTest( file1_name , file2_name );
			
			n++;
		}
	}
	
	bool RunTest ( const std::string& file1_name , const std::string& file2_name )
	{
		std::ifstream f_initial_data( file1_name , std::ios::binary );
		std::ifstream f_result( file2_name , std::ios::binary );
	
		
		using string_pool = std::vector<std::string>;
		
		string_pool vstr;
		
		vstr.reserve(10);
		std::string line;
		
		
		
		
		while( getline( f_initial_data , line ) )
		{
			vstr.push_back( line );
			line.clear();
			
		}
		
		long step = 0;
		double pos = 0;
		double expect = 0;
		
		if( vstr.size() > 0 )
		{
			pos = std::stod( vstr.back() );
		
			std::cout<<" pos = " << std::setprecision(11) << pos << std::endl;
		}

		vstr.clear();
		
		while( getline( f_result , line ) )
		{
			vstr.push_back( line );
			line.clear();		
		}
		
		
		
		if( vstr.size() > 1 ) 
		{
			expect = std::stod( vstr.back() );
			vstr.pop_back();
			step = std::stod( vstr.back() );
			vstr.pop_back();				
		}
		

		double actual = itests->run( pos );
		
						
		expect == actual ? std::cout << " true" << " expect = " << expect << " actual " << actual   : std::cout << " false" << " expect = " << expect << " actual " << actual  ;
		
		std::cout << std::endl;
	
		f_initial_data.close();
		f_result.close();
		
		return actual == expect;
	}
};
class Knight_Bitboard_Moves : public ITests
{
	unsigned long moves = 0;
	
	public:
	
	Knight_Bitboard_Moves() = default;
	~Knight_Bitboard_Moves() = default;
	Knight_Bitboard_Moves( const Knight_Bitboard_Moves& ) = default;
	Knight_Bitboard_Moves& operator = ( const Knight_Bitboard_Moves& ) = default;
	Knight_Bitboard_Moves( const Knight_Bitboard_Moves&& ) {}
	Knight_Bitboard_Moves& operator = ( const Knight_Bitboard_Moves && ){}
	
	unsigned long run( int pos )
	{		
		unsigned long long num = 1L << pos;
		
		int flag = 0;
		
		for( uint i = 0; i < 4; i++ )
		{
			if( ( pos >= 18 + ( 8 * i ) ) && ( pos <= 21 + ( 8 * i ) ) ) 
			{
				flag = true;
				break;
			}					
		}
		
		if( flag == true )
		{	
			moves = ( num >> 17 ) |  ( num >> 15 ) | ( num >> 10 ) | ( num >> 6 ) | ( num << 6 ) |  ( num << 10 ) | ( num << 15 ) | ( num << 17 );		
		}
		else
		{
			if( ( pos >= 2 ) && ( pos <= 5) )
			{	
				moves = ( num << 6 ) | ( num << 10 ) |  ( num << 15 ) | ( num << 17 );
			}
			else
			{
				if( ( pos >= 58 ) && ( pos <= 61 ) )
				{	
					moves = ( num >> 10 ) |  ( num >> 6 ) | ( num >> 17 ) | ( num >> 15 );	
				}
				else
				{
					if( ( pos == 40 ) || ( pos == 32 ) || ( pos == 24 ) || ( pos == 16 ) )
					{	
						moves = ( num >> 15 ) | ( num >> 6 ) | ( num << 10 ) | ( num << 17 );
					}
					else
					{
						if( ( pos == 47 ) || ( pos == 39 ) || ( pos == 31 ) || ( pos == 23 ) )
						{	
							moves = ( num >> 17 ) | ( num >> 10 ) | ( num << 6 ) | ( num << 15 );	
						}
						else
						{
							if( pos == 0 )
							{	
								moves = ( num << 10 ) | ( num << 17 );	
							}
							else
							{
								if( pos == 7 )
								{	
									moves = ( num << 6 ) | ( num << 15 );
								}
								else
								{
									if( pos == 56 )
									{	
										moves = ( num >> 15 ) | ( num >> 6 );	
									}
									else
									{
										if( pos == 63 )
										{	
											moves = ( num >> 10 ) | ( num >> 17 );	
										}
										else
										{
											if( pos == 1 )
											{
												moves = ( num << 10 ) | ( num << 15 ) | ( num << 17 );	
											}
											else
											{
												if( pos == 6 )
												{
													moves = ( num << 6 ) | ( num << 15 ) | ( num << 17 );	
												}
												else
												{
													if( pos == 57 )
													{
														moves = ( num >> 17 ) | ( num >> 15 ) | ( num >> 6 );	
													}
													else
													{
														if( pos == 62 )
														{
															moves = ( num >> 17 ) | ( num >> 15 ) | ( num >> 10 );
														}
														else
														{
															if( pos == 48 )
															{
																moves = ( num << 10) | ( num >> 6 ) | ( num >> 15 );
															}
															else
															{
																if( pos == 55 )
																{
																	moves = ( num << 6 ) | ( num >> 10 ) | ( num >> 17 );
																}
																else
																{
																	if( pos == 8 )
																	{
																		moves = ( num >> 6 ) | ( num << 10 ) | ( num << 17 );
																	}
																	else
																	{
																		if( pos == 15 )
																		{
																			moves = ( num >> 10 ) | ( num << 6 ) | ( num << 15 );
																		}
																		else
																		{
																			if( pos == 49 )
																			{
																				moves = ( num << 10 ) | ( num >> 6 ) | ( num >> 15 ) | ( num >> 17 );
																			}
																			else
																			{
																				if( pos == 54 )
																				{
																				moves = ( num << 6 ) | ( num >> 10 ) | ( num >> 15 ) | ( num >> 17);
																				}
																				else
																				{
																					if( pos == 9 )
																					{
																						moves = ( num << 15 ) | ( num << 17 ) | ( num << 10 ) | ( num >> 6);
																					}
																					else
																					{
																						if( pos == 14 )
																						{
																							moves = ( num << 6 ) | ( num << 15 ) | ( num << 17 ) | ( num >> 10 );
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}											
										}
									}
								}
							}
						}
					}
				}
			
			}
		
		}
	
		return moves;
	}
	
};
class King_Bitboard_Moves : public ITests
{
	unsigned long moves = 0;
	public:
	
	King_Bitboard_Moves() = default;
	~King_Bitboard_Moves() = default;
	King_Bitboard_Moves( const King_Bitboard_Moves& ) = default;
	King_Bitboard_Moves& operator = ( const King_Bitboard_Moves& ) = default;
	King_Bitboard_Moves( const King_Bitboard_Moves&& ) {}
	King_Bitboard_Moves& operator = ( const King_Bitboard_Moves && ){}
	
	unsigned long run( int pos )
	{		
		unsigned long long num = 1L << pos;
		
		int flag = 0;
		
		for( uint i = 0; i < 6; i++ )
		{
			if( ( pos >= 9 + ( 8 * i ) ) && ( pos <= 14 + ( 8 * i ) ) ) 
			{
				flag = true;
				break;
			}					
		}
		
		if( flag == true )
		{	
			moves = ( num >> 1 ) |  ( num >> 7 ) | ( num >> 8 ) | ( num >> 9 ) | ( num << 1 ) |  ( num << 7 ) | ( num << 8 ) | ( num << 9 );		
		}
		else
		{
			if( ( pos >= 1 ) && ( pos <= 6 ) )
			{	
				moves = ( num >> 1 ) | ( num << 1 ) |  ( num << 7 ) | ( num << 8 ) | ( num << 9 );	
			}
			else
			{
				if( ( pos >= 57 ) && ( pos <= 62 ) )
				{	
					moves = ( num >> 1 ) |  ( num >> 7 ) | ( num >> 8 ) | ( num >> 9 ) | ( num << 1 );	
				}
				else
				{
					if( ( pos == 48 ) || ( pos == 40 ) || ( pos == 32 ) || ( pos == 24 ) || ( pos == 16 ) || ( pos == 8 ) )
					{	
						moves = ( num >> 8 ) | ( num >> 7 ) | ( num << 1 ) | ( num << 8 ) | ( num << 9 );
					}
					else
					{
						if( ( pos == 55 ) || ( pos == 47 ) || ( pos == 39 ) || ( pos == 31 ) || ( pos == 23 ) || ( pos == 15 ) )
						{	
							moves = ( num >> 1 ) | ( num >> 8 ) | ( num >> 9 ) | ( num << 7 ) | ( num << 8 );	
						}
						else
						{
							if( pos == 0 )
							{	
								moves = ( num << 1 ) | ( num << 8 ) | ( num << 9 );	
							}
							else
							{
								if( pos == 7 )
								{	
									moves = ( num >> 1 ) |  ( num << 7 ) | ( num << 8 );	
								}
								else
								{
									if( pos == 56 )
									{	
										moves = ( num << 1 ) |  ( num >> 7 ) | ( num >> 8 );	
									}
									else
									{
										if( pos == 63 )
										{	
											moves = ( num >> 1 ) |  ( num >> 8 ) | ( num >> 9 );	
										}
									}
								}
							}
						}
					}
				}
			
			}
		
		}
	
		return moves;
	}
};

int bit_counter1 ( long data )
{
	int count = 0;
	
	for( int i = 0; i < sizeof( data ) * 8; i ++ )
	{
		if( ( data >> i ) & 1 ) count++;
	}
	return count;
}

int bit_counter2 ( long data )
{
	int count = 0;
	
	while( data )
	{
		data &= ( data -1 );
		count++;
	}
	return count;
}

int main ( int argc , char** argv )
{
	std::cout<<"algo4"<<std::endl;
	
	try
	{	
		#define EXP1 1
		#if EXP1
		{
			std::cout<<"--------------EXAMPLE1--------------"<<std::endl;
				   
			Tester test( "1.Bitboard - Король" , std::make_unique<King_Bitboard_Moves> () );
			test.RunTests();			
		}
		#endif
		
		#define EXP2 1
		#if EXP2
		{
			std::cout<<"--------------EXAMPLE2--------------"<<std::endl;
			
			Tester test( "2.Bitboard - Конь" , std::make_unique<Knight_Bitboard_Moves> ( ) );		
			
			test.RunTests();
		}
		#endif
		
		
		#define EXP3 1
		#if EXP3
		{
			std::cout<<"--------------EXAMPLE3--------------"<<std::endl;
			
			auto start = std::chrono::system_clock::now();
			
			std::cout<<"bit_counter1= " << bit_counter1(1234568765) << std::endl;
			
			auto end = std::chrono::system_clock::now();
       			std::chrono::duration<double> diff = end - start;	
       		
       			std::cout << " time left : " << diff.count() << " s\n";
		}
		#endif		
		
		#define EXP4 1
		#if EXP4
		{
			std::cout<<"--------------EXAMPLE4--------------"<<std::endl;
			
			auto start = std::chrono::system_clock::now();
			
			std::cout<<"bit_counter2 " << bit_counter2(1234568765) << std::endl;
			
			auto end = std::chrono::system_clock::now();
       			std::chrono::duration<double> diff = end - start;	
       		
       			std::cout << " time left : " << diff.count() << " s\n";
		}
		#endif	
	}
	catch( ... )
	{
		std::cout<<"error"<<std::endl;
	}
	
	

	return 0;
}





