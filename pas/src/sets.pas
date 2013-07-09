Unit sets; { Neue Version }
Interface

const setlimit	 = 255;   { Maximalgroesse fuer Mengen wie G und M }
type menge = set of 0..setlimit;

procedure union(var out,a,b : menge);
procedure intersect(var out,a,b : menge);
procedure restrict(var a,b : menge);
procedure difference(var m_out, m_from, m_in : menge);
procedure complement(var m_out, m_in : menge; maxelt :int64);
procedure fullset(var a	: menge);
procedure emptyset(var a : menge);
function is_empty(var a	: menge) : boolean;
function subset(var a,b : menge) : boolean;
function equal(var a,b : menge) : boolean;
procedure copy_menge(var m_out,m_in : menge);
procedure write_incidences(var a : menge; var setmax : int64);
procedure writeln_incidences(var a : menge; var setmax : int64);
procedure write_menge(var a : menge);
procedure writeln_menge(var a : menge);
procedure insert( e :int64; var a : menge);
procedure remove( e : int64; var a:menge);
procedure rtisegment(var xout,xin : menge; var ii : int64);

Implementation
 
procedure union(var out,a,b : menge);
{var ii :  int64;}
begin
      out := a + b;
end; { union }

procedure intersect(var out,a,b : menge);
begin
   out := a*b;
end; { intersect }

procedure restrict(var a,b : menge);
begin
   a := a*b;
end; { restrict }

procedure difference(var m_out, m_from, m_in : menge);
begin
   m_out := m_from - m_in;
end;

procedure complement(var m_out, m_in : menge; maxelt :int64);
begin
   m_out := [1..maxelt] - m_in; 
end; { complement }

procedure rtisegment(var xout,xin : menge; var ii : int64);
{ Restrict to initial segment }
begin
   xout := xin * [0..ii];
end; { restrict_to_initial_segment }

procedure emptyset(var a : menge);
begin
   a:=[];
end; { emptyset }

procedure fullset(var a	: menge);
begin
   a :=[0..setlimit];
end; { fullset }

function is_empty(var a	: menge) : boolean;
begin
   is_empty := (a = []);
end; { is_empty }

procedure copy_menge(var m_out,m_in: menge);
begin
   m_out:=m_in;
end; { copy_menge }

procedure insert(e : int64; var a:menge);
begin
   a:=a+[e..e];
end; { insert }

procedure remove(e : int64; var a:menge);
begin
   a:=a-[e..e];
end; { remove }

function subset(var a,b: menge) : boolean;
begin
   subset := a<=b;
end; { subset }

function equal(var a,b : menge):boolean;
begin
   equal := a=b;
end; { equal }

procedure write_incidences(var a : menge; var setmax : int64);
var ii :  int64;
begin
   for ii:= 1 to setmax do
      if (ii in a) then write('x') else write('.');
end; { write_incidences }

procedure writeln_incidences(var a : menge; var setmax : int64);
begin
   write_incidences(a,setmax);
   writeln;
end; { writeln_incidences }

procedure write_menge(var a : menge);
var ii	: int64;
   erst	: boolean;
begin
   write('{');
   erst:=true;
   for ii := 0 to setlimit do
      if (ii in a) then
      begin
	 if erst then erst := false else write(',');
	 write(ii);
      end;
   write('}');
end; { write_menge }

procedure writeln_menge(var a : menge);
begin
   write_menge(a);
   writeln;
end; { writeln_menge }

end.		       








