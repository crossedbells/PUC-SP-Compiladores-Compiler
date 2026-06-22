program factor;

var
  n : integer;
  d : integer;

begin
  n := paramstr(1);

  if n < 2 then
    writeln(n)
  else
    begin
      d := 2;
      while d * d <= n do
        begin
          while (n mod d) = 0 do
            begin
              write(d);
              write(' ');
              n := n div d
            end;
          d := d + 1
        end;
      if n > 1 then
        writeln(n)
    end
end.
