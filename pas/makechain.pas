program makechains; {computes all maximal chains}

uses sets, contexts;

const
   MAXNOC = 3300; {Maximum number of concepts}
   MAXNB  = 200;  {Maximum number of lower neighbors}

type setvec =  array[1..MAXNOC] of menge;

var
   Intent	     : setvec;
   Lower	     : array[1..MAXNOC,0..MAXNB] of integer;
   chain, branch     : array[1..MAXNOC] of integer;
   i,j,k,l,noc,count : Integer;
   kk,ll	     : context;
   A,B		     : menge;
   neigh, up, ende   : boolean;
   request	     : integer;
   name		     : string;

begin
   ask_for_cxt(kk);
   write('Which chain? ');readln(request);
   first_intent(A,kk);
   i := 0;
   repeat
      i := succ(i);
      intent[i] := A;
   until not next_intent(A,KK);
   noc := i;
   for i := 1 to pred(noc) do
   begin
      Lower[i,0] := 0;
      for k := succ(i) to noc do
	 if subset(Intent[i],Intent[k]) then
	 begin
	    j := 1;
	    neigh := true;
	    while (j <= Lower[i,0]) and neigh do
	    begin
	       if subset(Intent[Lower[i,j]],Intent[k]) then neigh := false;
	       j := succ(j);
	    end;
	    if neigh then
	    begin
	       Lower[i,0] := succ(Lower[i,0]);
	       Lower[i,Lower[i,0]] := k;
	    end;
	 end;
   end;
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
		  if count = request then
		  begin
		     new_context(kk.gnum,kk.mnum,ll);
		     for j := 2 to pred(i) do
		     begin
			A:=intent[chain[j]];
			make_extent(B,A,kk);
			write('(');
			write_menge(B);
			write(',');
			write_menge(A);
			writeln(')');
			for k := 1 to kk.gnum do
			   if k in B then
			      for l := 1 to kk.mnum do
				 if l in A then make_incident(k,l,ll);
		     end;
		  end;
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
   writeln('Number of formal concepts: ',noc);
   writeln('Number of maximal chains: ',count);
   writeln('Ferrers relation written to file Ferrers.cxt');
   writeln;
   Str(request,name);
   ll.name := kk.name+'-chain'+name;
   name := 'Ferrers';
   write_context(ll,name);
end.
   