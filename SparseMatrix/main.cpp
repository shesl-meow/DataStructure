#include "sparse-matrix.cpp"

int main()
{
    unsigned int a = 0, b = 0, c = 0;
    std::cout << "colmn and row for matrix:";
    if( std::cin >> a >> b )
    {
        SparseMatrix<double> m(a, b);
        m.display();
        while(1)
        {
            std::string command;
            std::cout << "set or get?(start from zero)";
            std::cin >> command;
            if(command == "set"){
                std::cout << "Please enter 'row', 'colmn' and 'data' in order:";
                std::cin >> a >> b >> c;
                m.set(a, b, c);
            }else if(command == "get"){
                std::cout << "Please enter 'row' and 'colmn' in order:";
                std::cin >> a >> b;
                std::cout << "You get: " << m.get(a,b) << std::endl;
            }else{
                std::cout << "Invalid command, please enter again!" << std::endl;
            }
            m.display();
        }
    }else{
        std::cerr << "input error!!" << std::endl;
        exit(1);
    }
    return 0;
}