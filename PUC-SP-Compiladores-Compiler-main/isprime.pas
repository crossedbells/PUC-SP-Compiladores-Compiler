program isprime;

var
  n    : integer;
  i    : integer;
  flag : boolean;

begin
  n    := paramstr(1);
  flag := true;

  if n < 2 then
    flag := false
  else
    begin
      i := 2;
      while (i * i) <= n do
        begin
          if (n mod i) = 0 then
            flag := false;
          i := i + 1
        end
    end;

  if flag then
    writeln(true)
  else
    writeln(false)
end.
