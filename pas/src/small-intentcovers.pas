program extentcover; {Computes covers of by attribute extents}
{ Warning: Input matrix is transposed, attribute extents are rows. }

uses contexts, sets, tricks;

const
   MAXCSET	  = 10000; {Maximum number of covering sets}
   MAXSEARCHDEPTH = 15;

 var
    cset       : array[1..MAXCSET] of menge;
    nextmax,S  : array[0..MAXCSET,1..MAXSEARCHDEPTH] of int64;
    G	       : array[0..MAXSEARCHDEPTH] of menge;
    sol,finsol : array[0..MAXSEARCHDEPTH] of int64;
    i,pri,prj  : int64;
    ub,ncol,gp : int64;
    depth,gnum : int64;
    geg	       : int64;
    A,B	       : menge;
    ruleout    : boolean;
    dataname   : string;

procedure readin; {reads the data from file}
var
   datafile : text;
   str	    : string;
   ii,jj    : int64;
begin
   write('Data file: ');
   readln(str);
   writeln;
   add_suffix(str,'cxt');
   assign(datafile,str);
   reset(datafile);
   readln(datafile);
   readln(datafile,dataname);
   readln(datafile,ncol);
   readln(datafile,gnum);
   readln(datafile);
   for ii := 1 to ncol do readln(datafile);
   for ii := 1 to gnum do readln(datafile);
   G[1] := [1..gnum];
   nextmax[0,1] := 1;
   for ii := 1 to ncol do
   begin
      nextmax[ii,1] := succ(ii);
      cset[ii] := [];
      readln(datafile,str);
      for jj := 1 to gnum do if (str[jj] in ['x','X']) then
	 cset[ii] := cset[ii]+[jj];
   end;
   close(datafile);
   nextmax[ncol,1] := 0;
   for ii := 1 to ncol do writeln_incidences(cset[ii],gnum);
end; { readin }

procedure maxify; { Eliminates non-maximal rows }
var ii, jj : int64;
begin
   pri := 0;
   repeat
      ii := nextmax[pri,depth];
      ruleout := false;
      if ii <> 0 then
      begin
	 A := Cset[ii]*G[depth];
	 jj := nextmax[ii,depth];
	 prj := ii;
	 while (jj <> 0) and not ruleout do
	 begin
	    B := Cset[jj]*G[depth];
	    if  subset(B,A) then
	    begin
	       nextmax[prj,depth] := nextmax[jj,depth];
	    end else prj := jj;
	    if (A<>B) and subset(A,B) then ruleout := true;
	    jj := nextmax[jj,depth];
	 end;
	 if ruleout then nextmax[pri,depth] := nextmax[ii,depth]
	 else pri := ii;
      end;
   until nextmax[ii,depth] = 0;
end; { maxify }

function small_intent : int64;  
var
   freq	      : array[1..256] of int64;
   ii,jj,c,mn : int64;
   carrier    : menge;
begin
   for ii := 1 to gnum do freq[ii] := 0;
   c := 0;
   while nextmax[c,depth] <> 0 do
   begin
      c := nextmax[c,depth];
      carrier := G[depth]*cset[c];
      for ii := 1 to gnum do
	 if ii in carrier then freq[ii] := succ(freq[ii]);
   end;
   mn := MAXCSET;
   for ii := 1 to gnum do if ii in G[depth] then
      if freq[ii] < mn then
      begin
	 mn := freq[ii];
	 geg := ii;
      end;
   small_intent := mn;
   S[0,depth] := 0;
   ii := 0;
   jj := 0;
   while nextmax[ii,depth] <> 0 do
   begin
      ii := nextmax[ii,depth];
      if geg in cset[ii] then
      begin
	 S[jj,depth] := ii;
	 jj := ii;
      end;
   end;
   S[jj,depth] :=0;
end; { small_intent }

procedure init;
begin
   readin;
   depth := 1;
   ub := succ(MAXSEARCHDEPTH);
   sol[0] := 0;
end; { init }

function fullcolumn: boolean;
var jj,ij :  int64;
begin
   fullcolumn := false;
   jj := nextmax[0,depth];
   while (jj > 0) and not subset(G[depth],cset[jj]) do
   begin
      jj := nextmax[jj,depth];
   end;
   fullcolumn := (jj <> 0);
   if jj <> 0 then
      begin
	 sol[depth] := jj;
	 sol[0] := depth;
	 ub := depth;
	 write('!');
	 for ij := 0 to ub do finsol[ij] := sol[ij];
      end;
end; { fullcolumn }

procedure backtrack;
begin
   repeat
      write('d');
      depth := pred(depth);     
   until (depth = 0) or (S[0,depth]<>0);
end; { backtrack }

procedure increment;
var mm,predepth : int64;
begin
   write('u');
   mm := S[0,depth];
   S[0,depth] := S[S[0,depth],depth];
   sol[depth] := mm;
   predepth := depth;
   depth := succ(depth);
   G[depth] := G[predepth] - cset[mm];
   i := 0;
   while nextmax[i,predepth] <> 0 do
   begin
      if nextmax[i,predepth] = mm then
	 nextmax[i,predepth] := nextmax[nextmax[i,predepth],predepth];
      nextmax[i,depth] :=  nextmax[i,predepth];
      i := nextmax[i,predepth];
   end;
end; { increment }

{                        MAIN                            }
begin
   init;
   writeln('Pruning sequence, u=up, d=down, !=found, #=end : '); 
   repeat
      maxify;
      gp := small_intent;
      if (depth = 1) and (gp = 0) then
         	 writeln('No solution possible: object ',geg:3,' has no attributes.');
      if (gp > 0) then
      begin
	        if fullcolumn or (ub = succ(depth)) then 
	                 backtrack 
	           else increment;
      end else backtrack;
   until depth < 1;
   writeln('#');
   if ub <= MAXSEARCHDEPTH then
   begin
      write('Cover found of size ',ub,', consisting of object intents ');
      writeln;
      for i := 1 to ub do
      begin
		writeln('#CHAIN ',finsol[i]);
	 {if i < ub then write(', ') else writeln('.');}
      end;
      for i := 1 to ub do writeln_menge(cset[finsol[i]]);
   end;
   writeln;
end.
