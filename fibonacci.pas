program fibonacci;

var
  n    : integer;
  a    : integer;
  b    : integer;
  tmp  : integer;
  i    : integer;

begin
  n := paramstr(1);

  if n <= 0 then
    writeln(0)
  else
    begin
      a := 1;
      b := 1;
      i := 2;
      while i < n do
        begin
          tmp := a + b;
          a   := b;
          b   := tmp;
          i   := i + 1
        end;
      writeln(b)
    end
end.
