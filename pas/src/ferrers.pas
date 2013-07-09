program ferrers; { Computes maximal Ferrers relations inside the incidence }

uses contexts, sets;

const
   MAXNOCONCEPTS = 50000;
   MAXNEIGHBORS	 = 300;
   MAXNOCHAINS	 = 500000;
   
var
   cset		   : array[1..MAXNOCHAINS] of menge;
   cnam		   : array[1..MAXNOCHAINS] of string;
   cmax		   : array[1..MAXNOCHAINS] of boolean;
   tset		   : array[1..MAXNOCONCEPTS] of menge;
   Lower	   : array[1..MAXNOCONCEPTS,0..MAXNEIGHBORS] of int64;
   kk		   : context;
   gdup,mdup	   : array[1..setlimit] of boolean;
   gtight,mtight   : array[1..setlimit] of int64;
   nconcept,ntight : int64;
   ntc,c,d	   : int64;
   outfile	   : text;

procedure make_tights;   {   Computes the tight incidences.  }
var
   Up, Down	 : array[1..setlimit] of menge;
   g,h,m,n	 : int64;

   function is_tight(gg,mm : int64) : boolean;
   var gh, mn : int64;
   begin      
      is_tight := incident(gg,mm,kk) and not (gdup[gg] or mdup[mm]);
      for gh := 1 to kk.gnum do
	 if (gh in up[gg]) and incident(gh,mm,kk) then is_tight := false;
      for mn := 1 to kk.mnum do
	 if (mn in down[mm]) and incident(gg,mn,kk) then is_tight := false;
   end;
   
begin
   ask_for_cxt(kk);
   make_columns(kk);
   for g := 1 to kk.gnum do
      begin
	 Up[g] := [];
	 gdup[g] := false;
      end;
   for m := 1 to kk.mnum do
      begin
	 Down[m] := [];
	 mdup[m] := false;
      end;
   for g := 1 to kk.gnum do if not gdup[g] then
   begin
      for h := 1 to pred(g) do
	 if subset(kk.row[h],kk.row[g]) then Up[g] := Up[g]+[h];
      for h := succ(g) to kk.gnum do
      begin
	 if kk.row[g] = kk.row[h] then gdup[h] := true else
	 begin	    
	    if subset(kk.row[h],kk.row[g]) then Up[g] := Up[g]+[h]
	 end;
      end;
   end;
   for m := 1 to kk.gnum do if not mdup[m] then
   begin
      for n := 1 to pred(m) do
	 if subset(kk.column[n],kk.column[m]) then Down[m] := Down[m]+[n];
      for n := succ(m) to kk.mnum do
      begin
	 if kk.column[m] = kk.column[n] then mdup[n] := true else
	 begin	    
	    if subset(kk.column[n],kk.column[m]) then Down[m] := Down[m]+[n]
	 end;
      end;
   end;
   ntight := 0;
   for g := 1 to kk.gnum do
      for m := 1 to kk.mnum do if is_tight(g,m) then
      begin
	 ntight := succ(ntight);
	 gtight[ntight] := g;
	 mtight[ntight] := m;
      end;
end; { make_tights }

procedure tightsets;  { Computes tight incidences for each concept  }
var A,B	: menge;
   tc	: int64;
begin
   nconcept := 1;
   first_intent(B,kk);
   tset[1] := [];
   while next_intent(B,kk) do
   begin
      nconcept := succ(nconcept);
      tset[nconcept] := [];
      make_extent(A,B,kk);
      for tc := 1 to ntight do
	 if (gtight[tc] in A) and (mtight[tc] in B) then
	    tset[nconcept] := tset[nconcept]+[tc];
   end;
end; { tightsets }

procedure diagram; {   Computes the neighborhood relation   }
var
   lowintent   : array[1..MAXNEIGHBORS] of menge;
   count,ii,jj : int64;
   A,B	       : menge;
   neigh       : boolean;
begin
   count := 0;
   first_intent(B,kk);
   repeat
      count := succ(count);
      Lower[count,0] := 0;
      ii := count;
      A := B;
      while next_intent(A,kk) do
      begin
	 ii := succ(ii);
	 neigh := subset(B,A);
	 if neigh and (Lower[count,0] > 0) then
	    for jj := 1 to Lower[count,0] do
	       if subset(lowintent[jj],A) then
		  neigh := false;  { hier kann man noch effizienter sein! }
	 if neigh then
	 begin
	    Lower[count,0] := succ(Lower[count,0]);
	    Lower[count,Lower[count,0]] := ii;
	    lowintent[Lower[count,0]] := A;
	 end;
      end;
   until (not next_intent(B,kk));
end; { diagram }

procedure maxchains;
var
   chain,branch	: array[1..MAXNOCONCEPTS] of int64;
   count, i	: int64;
   up,ende	: boolean;

   procedure register;
   var
      jj	  : int64;
      cname,dname : string;
      T		  : menge;
      alive	  : boolean;
   begin
      T := [];
      cname := '';
      for jj := 1 to i do
	 begin
	    T := T + tset[chain[jj]];
	    Str(count,cname);
	 end;
      if ntc > 0 then
      begin
	 alive := true;
	 jj := 0;
	 while (jj < ntc) and alive do
	 begin
	    jj := succ(jj);
	    if cmax[jj] then
	    begin
	       if T <= cset[jj] then alive := false
	       else if cset[jj] <= T then cmax[jj] := false;
	    end;
	 end;
	 if alive then
	 begin
	    ntc := succ(ntc);
	    cset[ntc] := T;
	    cnam[ntc] := cname;
	    cmax[ntc] := true;
	 end;
      end else
      begin
	 ntc := 1;
	 cset[ntc] := T;
	 cnam[ntc] := cname;
	 cmax[ntc] := true;
      end;
   end; { register }

begin
   ntc := 0;
   count := 0;
   i := 1;
   chain[i] := 1;
   branch[i] := 1;
   up := true;
   ende := (Lower[1,0] = 0);
   while not ende do
   begin
      if up then
      begin
	 if (Lower[chain[i],0] <> 0) then
	    begin
	       i := succ(i);
	       chain[i] := Lower[chain[pred(i)],branch[pred(i)]];
	       branch[i] := 1;
	    end else
	       begin
		  up := false;
		  count := succ(count);
		  if (count mod 100)=0 then write('#'); 
		  register;
	       end;
      end;
      if not up then if branch[pred(i)] < Lower[chain[pred(i)],0] then
      begin
	 branch[pred(i)] := succ(branch[pred(i)]);
	 chain[i] := Lower[chain[pred(i)],branch[pred(i)]];
	 branch[i] := 1;
	 up := true;
      end else
      begin
	 i := pred(i);
	 if i = 0 then ende := true;
      end;
   end;
   writeln;
   writeln('Number of maximal chains: ',count);
end; { maxchains }

begin
   make_tights;
   write('tights ');
   tightsets;
   write('tightsets ');
   diagram;
   write('diagram ');
   maxchains;
   d := 0;
   for c := 1 to ntc do if cmax[c] then 
   begin
      d := succ(d);
      write_incidences(cset[c],ntight);
      writeln(' #FERRERS ',d:4,' #MAKECHAIN ',cnam[c]:6);
   end;
   writeln(d,' maximal Ferrers relations found inside the incidence relation.');
   write('Output written to file ',kk.name+'chains.cxt ');
   writeln('for use with program >intentcover<.');
   write('You might want to invoke program > makechain < ');
   writeln('to see the Ferrers relation.');
   writeln('It will ask for the file name ',kk.name,'.cxt and for one of');
   writeln('the numbers in the last column above.');
   writeln;
   assign(outfile,kk.name+'chains.cxt');
   rewrite(outfile);
   writeln(outfile,'L');
   writeln(outfile,kk.name);
   writeln(outfile,d);
   writeln(outfile,ntight);
   writeln(outfile);
   for c := 1 to ntc do
      if cmax[c] then writeln(outfile,cnam[c]);
   for c := 1 to ntight do
      writeln(outfile,'(',gtight[c],',',mtight[c],')');
   for c := 1 to ntc do if cmax[c] then 
      begin
	 for d := 1 to ntight do
	    if (d in cset[c]) then write(outfile,'x')
	    else write(outfile,'.');
	 writeln(outfile);
      end;
   close(outfile);
end.
