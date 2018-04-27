clear
close ALL
f=double(imread('sq.bmp')) ;
[m, n] = size(f) ;

for i = 2:m-1
  for j = 2:n-1
    acc=0 ;
    for k=-1:1
        for l=-1:1
         acc= acc+abs(f(i,j)-f(i-k,j-l))  ;  
        end
    end
     acc=acc/8 ;
     g(i,j) = acc ;                  
   end
end

g1=g ;
mx=max(max(g)) ;
g2=(g==mx) ;
n_corners=sum(sum(g2))
nc=sum(sum(g2)) 
  for i = 2:m-1
   for j = 2:n-1 
     if g(i,j) == mx 
      g(i,j)=0 ;
      g1(i-1:i+1,j-1:j+1)=255 ; 
     end
   end
  end

figure(1)
subplot(221), image(255*f)
colormap(gray(256))

subplot(222),image(255*g)
colormap(gray(256))

 figure(2)
 image(g1)
 colormap(gray(256))

