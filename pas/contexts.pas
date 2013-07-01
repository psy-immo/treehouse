Unit contexts;

{ ----------------------------------------------------------------- }
{                  Kontextoperationen                               }
{ ----------------------------------------------------------------- }

Interface
uses sets,tricks,jdk15;


type
   context = record	
		gnum, mnum	: integer;
		row,column	: array[1..setlimit] of menge;
		name		: string[80];
		columns_defined	: boolean;
	     end;		
   

procedure make_extent(var a_out,b_in : menge; var kk:context);

procedure make_columns(var kk :  context);

procedure close_extent(var a_out,a_in : menge; var kk:context);

procedure make_intent(var b_out,a_in : menge; var kk:context);

procedure close_intent(var b_out,b_in : menge; var kk : context);

procedure first_intent(var b_out : menge; var kk : context);

procedure first_extent(var b_out : menge; var kk : context);

function next_intent(var a : menge; var kk : context) : boolean;

function next_extent(var a : menge; var kk : context) : boolean;

procedure new_context(gzahl,mzahl : integer; var kk:context);

procedure read_cxt(var kk : context; var filename:string);

procedure write_context(var kk : context; var filename : string);

procedure ask_for_cxt(var kk : context);

procedure make_incident(g,m : integer; var kk:context);
			       
procedure make_nonincident(g,m : integer; var kk:context);

function incident(g,m : integer; var kk : context) : boolean;

procedure complement_context(var kkout, kkin :  context);

procedure copy_context(var kkout, kkin :  context);

function number_of_concepts(var kk :  context): integer;

procedure flip_rows(var g,h : integer; var kk: context);

procedure flip_columns(var m,n : integer; var kk : context);

Implementation

procedure make_extent(var a_out,b_in : menge; var kk:context);
var ii :  integer;
begin with kk do begin
   emptyset(a_out);
   for ii := 1 to gnum do
      if subset(b_in,row[ii]) then insert(ii,a_out);
end;end; { make_extent }

procedure make_columns(var kk :  context);
var ii,jj :  integer;
begin with kk do begin
   for ii := 1 to mnum do
   begin
      emptyset(column[ii]);
      for jj := 1 to gnum do
	 if ii in row[jj] then insert(jj,column[ii]);
   end;
   columns_defined:=true;
end;end; { make_columns }

procedure close_extent(var a_out,a_in : menge; var kk:context);
var ii  : integer;
begin with kk do begin
   if not columns_defined then make_columns(kk);
   a_out := [1..kk.gnum];
   for ii := 1 to mnum do
      if subset(a_in,column[ii]) then restrict(a_out,column[ii]);
end;end; { close_extent }

procedure make_intent(var b_out,a_in : menge; var kk:context);
var ii : integer;
begin with kk do begin
   b_out:=[1..kk.mnum];
   for ii := 1 to gnum do
      if ii in a_in then restrict(b_out,row[ii]);
end;end; { make_intent }

procedure close_intent(var b_out,b_in : menge; var kk : context);
var ii	   : integer;
begin with kk do begin
   b_out:=[1..kk.mnum];
   for ii := 1 to gnum do
      if subset(b_in,row[ii]) then restrict(b_out,row[ii]);
end;end; { close_intent }

procedure first_intent(var b_out : menge; var kk : context);
var empty : menge;
begin with kk do begin
   emptyset(empty);
   close_intent(b_out,empty,kk);
end;end; { first_intent }

procedure first_extent(var b_out : menge; var kk : context);
var empty : menge;
begin with kk do begin
   emptyset(empty);
   close_extent(b_out,empty,kk);
end;end; { first_extent }

function next_intent(var a : menge; var kk : context) : boolean;
var ii	  : integer;
   erfolg : boolean;
   function probiere(var x: menge; pp : integer) : boolean;
   var huelle,sgment : menge;
      ergebnis	      : boolean;
   begin with kk do begin
      insert(pp,x);
      close_intent(huelle,x,kk);
      rtisegment(sgment,huelle,pp);
      ergebnis:=subset(sgment,x);
      if ergebnis then copy_menge(x,huelle) else remove(ii,x);
      probiere := ergebnis;
   end;end;
begin with kk do begin
   ii:=succ(mnum);
   erfolg := false;
   repeat
      ii:=pred(ii);
      if not (ii in a) then
	 erfolg := probiere(a,ii)
      else remove(ii,a);
   until erfolg or (ii=1);
   next_intent:=erfolg;
end;end; { next_intent }

function next_extent(var a : menge; var kk : context) : boolean;
var ii	  : integer;
   erfolg : boolean;
   function probiere(var x: menge; pp : integer) : boolean;
   var huelle,sgment : menge;
      ergebnis	      : boolean;
   begin with kk do begin
      insert(pp,x);
      close_extent(huelle,x,kk);
      rtisegment(sgment,huelle,pp);
      ergebnis:=subset(sgment,x);
      if ergebnis then copy_menge(x,huelle) else remove(ii,x);
      probiere := ergebnis;
   end;end;
begin with kk do begin
   ii:=succ(gnum);
   erfolg := false;
   repeat
      ii:=pred(ii);
      if not (ii in a) then
	 erfolg := probiere(a,ii)
      else remove(ii,a);
   until erfolg or (ii=1);
   next_extent:=erfolg;
end;end; { next_extent }

procedure new_context(gzahl,mzahl : integer; var kk:context);
var ii : integer;
begin with kk do begin
   gnum := gzahl;
   mnum := mzahl;
   columns_defined := false;
   for ii:=1 to gnum do emptyset(row[ii]);
end;end; { new_context }

procedure read_cxt(var kk : context; var filename : string);
var cxtfile : text;
   i,j	    : integer;
   zeile    : string[setlimit];
begin
   add_suffix(filename,'cxt');
   assign(cxtfile,filename);
   add_suffix(filename,'');
   filename[0] := pred(filename[0]);
   reset(cxtfile);
   readln(cxtfile);
   readln(cxtfile,kk.name);
   if (kk.name = '')or (kk.name = ' ') then kk.name := filename;
   readln(cxtfile,kk.gnum);
   readln(cxtfile,kk.mnum);
   new_context(kk.gnum,kk.mnum,kk);
   for i := 0 to kk.gnum do readln(cxtfile); 
   for i := 1 to kk.mnum do readln(cxtfile);
   with kk do
   begin
      for i := 1 to gnum do
      begin
	 readln(cxtfile,zeile);
	 emptyset(row[i]);
	 for j := 1 to mnum do
	    if zeile[j] in ['x','X'] then insert(j,row[i]);
      end;
   end;
end; { read_cxt }

procedure write_context(var kk : context; var filename : string);
var cxtfile : text;
   gg,mm    : integer;
begin with kk do begin
   add_suffix(filename,'cxt');
   assign(cxtfile,filename);
   rewrite(cxtfile);
   writeln(cxtfile,'B');
   writeln(cxtfile,name);
   writeln(cxtfile,gnum);
   writeln(cxtfile,mnum);
   writeln(cxtfile);
   for gg := 1 to gnum do writeln(cxtfile,'G',gg);
   for mm := 1 to mnum do writeln(cxtfile,'M',mm);
   for gg := 1 to gnum do
   begin
      for mm := 1 to mnum do
	 if incident(gg,mm,kk) then write(cxtfile,'X') else write(cxtfile,'.');
      writeln(cxtfile);
   end;
   close(cxtfile);
end;end; { write_context }

procedure ask_for_cxt(var kk : context);
var zeile : string[setlimit];
begin
   writeln;
   write('Kontext Filename: ');
   readln(zeile);
   add_suffix(zeile,'cxt');
   read_cxt(kk,zeile);
end; { ask_for_cxt }

procedure make_incident(g,m : integer; var kk:context);
begin with kk do begin
   insert(m,row[g]);
   columns_defined:=false;
end;end;

procedure make_nonincident( g,m : integer; var kk:context);
begin with kk do begin
   remove(m,row[g]);
   columns_defined:=false;
end;end;

function incident(g,m : integer; var kk : context) : boolean;
begin
   incident := m in kk.row[g];
end; { incident }

procedure complement_context(var kkout, kkin: context);
var g :  integer;
begin
   new_context(kkin.gnum,kkin.mnum,kkout);
   for g := 1 to kkin.gnum do
      kkout.row[g]:=[1..kkin.mnum] - kkin.row[g];
end; { complement_context }

procedure copy_context(var kkout, kkin :  context);
{ Legt eine Kopie von kkin in kkout an. }
var g :  integer;
begin
   new_context(kkin.gnum, kkin.mnum, kkout);
   for g := 1 to kkin.gnum do
      copy_menge(kkout.row[g],kkin.row[g]);
end; { copy_context }

function number_of_concepts(var kk :  context): integer;
var count : integer;
   B	  : menge;
begin
   first_intent(B,kk);
   count := 0;
   repeat count := succ(count);
   until not next_intent(B,kk);
   number_of_concepts := count;
end; { number_of_concepts }

procedure flip_rows(var g,h : integer; var kk: context);
var S :  menge;
begin
   copy_menge(S,kk.row[g]);
   copy_menge(kk.row[g],kk.row[h]);
   copy_menge(kk.row[h],S);
end; { flip_rows }

procedure flip_columns(var m,n : integer; var kk : context);
var flag : boolean;
       g : integer;
begin
   for g:= 1 to kk.gnum do
   begin
      flag := incident(g,m,kk);
      if incident(g,n,kk) then make_incident(g,m,kk) else
	 make_nonincident(g,m,kk);
      if flag then  make_incident(g,n,kk) else
	 make_nonincident(g,n,kk);
   end;
end; { flip_columns }

end.	 






