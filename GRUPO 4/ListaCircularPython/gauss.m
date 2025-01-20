



function[X]=gauss_jordan(A,B);
    A=input("Ingrese una matriz cuadrada entre corchetes:");
    B=input("Ingrese una matriz columna entre corchetes");
    
    n=size(A);
    if n(1)
    dett=det(a);
    sz=size(a);
    [n(1),n(2)]=size(a);
    sc=size(b);
    n=n(1);
    if sz(1,1)~=sz(1,2)&& sz(1,1)~=sc(1,1)
        disp("No se pudo resolver");
    else 
        if dett==0
        disp("No existe una solucion");
        else
        A=[a,b'];    
        disp("Si existe una solucion");
        for j=1:n-1
            for i=j+1:n
                A(i,:)=A(i,:)-A(i,j)*A(j,:)/A(j,j);
            end
        end
        x=zeros(n,1);
    x(n)=A(n,end)/A(n,n);
    for i=n-1:-1:1
        sum=A(i,end);
       for j=i+1:n
        sum=sum-A(i,j)*x(j);
       end
       x(i)=sum/A(i,i);
    end
        end 
    end
    
    c=a*x;
    disp(c);
    
    
    %subrutina para la matriz escalonada
    