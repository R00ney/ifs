
z = ones(64,64)*3;

for row = 1:64
    for col = 1:64
        z(row,col) = ((col - 32)^2+(row-32)^2) < 22^2;
    end
end

z
