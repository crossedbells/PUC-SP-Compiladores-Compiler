program TesteCompilador;
var
    i : integer;
begin
    i := 1;
end.

function Fatorial(n: integer): integer;
begin
    if n <= 1 then
        return 1
    else
        return n * Fatorial(n - 1);
end;

begin
    x := Fatorial(5);
    writeln(x);

    for i := 1 to 3 do
    begin
        write(i);
    end;
    writeln();
end.