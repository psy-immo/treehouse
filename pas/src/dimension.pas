Unit dimension;
Interface
uses sets,tricks,contexts;
type
        LC=record
                lcm:array[1..100] of menge;
                lcn:int64;
                sett:menge;     {union}
        end;

type
        ints=record
                m:array[1..100] of menge;     {intents}
                nm:int64;                   {nr int}
                lc:array[1..100] of LC;       {leastConc}
                upn:array[1..100] of LC;        {up_neigh}
                ex:array[1..100] of menge; {extents}
        end;

procedure delete_ints(var v:ints;var k:int64)  ;
procedure leastConcurent(var v:ints);
procedure delete_LC(var v:LC;var x:menge) ;
procedure load(var v:ints;var con:context);
procedure union_all(var l:LC);
procedure printContext(var v:ints);
procedure makeUpn(var v:ints;var k:context);

Implementation

procedure union_all(var l:LC);   {vector to set}
var i:int64;
begin
        for i:=1 to l.lcn do
        begin
                union(l.sett,l.sett,l.lcm[i]);
        end;
end;

{procedure delete_ints(var v:ints;var k:int64) ;
var i:int64;
begin
        for i:=k to v.nm-1 do
        begin
                v.m[i]:=v.m[i+1];
        end;
        v.nm:=v.nm-1;
end;                              }

procedure delete_LC(var v:LC;var x:menge) ;            {delete lc,remake vector}
var i,j:int64;
begin

        j:=1;

        while ((j<=v.lcn) and not(equal(x,v.lcm[j])))  do
        begin

				j:=j+1;
	end;
        for i:=j to v.lcn-1 do
        begin
                v.lcm[i]:=v.lcm[i+1];
        end;
        if j<=v.lcn then
        v.lcn:=v.lcn-1;
end;

procedure load(var v:ints;var con:context);    {make intents}
var
i,j:int64;
ok:Boolean;
a,b:menge;
begin
        v.nm:=0;
        for i:=1 to 100 do
        begin
            v.lc[i].lcn:=0;
            v.upn[i].lcn:=0;
        end;
        ok:=true;
        first_intent(a,con);
        while(ok) do
        begin
                v.nm:=v.nm+1;
                v.m[v.nm]:=a;
                make_extent(b,a,con);
                v.ex[v.nm]:=b;
                ok:=next_intent(a,con);
        end;
end;



procedure leastConcurent(var v:ints);
var
len,i,j,jj,k,copy:int64;
a:array[1..100] of menge;
b:array[1..100] of menge;
x:menge;
begin
        for i:=1 to v.nm do
        begin
                for j:=1 to v.nm do
                begin
                        if not(subset(v.m[i],v.m[j])) and not(subset(v.m[j],v.m[i])) then
                        begin
                               v.lc[i].lcn:=v.lc[i].lcn+1;
                               v.lc[i].lcm[v.lc[i].lcn]:=v.m[j];
                        end;
                end;
                len:=v.lc[i].lcn;
                 jj:=1;
                for j:=1 to len do
                begin
                        a[j]:=v.lc[i].lcm[j];
                        b[j]:=v.lc[i].lcm[j];
                        end;
                j:=1; copy:=len;
                while j<=copy do
                begin
                        jj:=1;
                        while jj<=copy do
                        begin
                        writeln('Compar');
                        write_menge(v.lc[i].lcm[jj]);
                        write_menge(v.lc[i].lcm[j]);
                                if (subset(b[jj],a[j]) and
                                      not(equal(a[j],b[jj]))) then
                                begin
                                         x:=b[jj];
                                        delete_LC(v.lc[i],x);


                                 end;

                             jj:=jj+1;

                        end;
                        writeln('');
                        j:=j+1;
                end;
                union_all(v.lc[i]);

end;
end;
{procedure makeUpn(var v:ints;var k:context);
var temp2,g,Gi,temp,up:menge;
i,j,jj:int64;
begin
        g:=[1..k.gnum];

        for i:=1 to v.nm do
        begin
                difference(Gi,g,v.ex[i]);
                for j:=1 to setlimit do
                        if ( j in Gi) then
                        begin
                                emptyset(temp);
                                insert(j,temp);
                                union(temp,v.ex[i],temp);
                                copy_menge(up,temp);
                                make_intent(temp,temp,k);
                                make_extent(temp,temp,k);
                                difference(temp,temp,v.ex[i]);
                                for jj:=1 to setlimit do
                                begin
                                        if ( jj in temp) then
                                        begin
                                                emptyset(temp2);
                                                insert(jj,temp2);
                                               make_intent(temp2,temp2,k);
                                               make_extent(temp2,temp2,k);
                                               writeln('temp1 si 2');
                                               write_menge(temp);
                                               writeln();
                                               write_menge(temp2);
                                                if equal(temp2,temp) then
                                                begin
                                                        v.upn[i].lcn:=v.upn[i].lcn+1;
                                                        v.upn[i].lcm[v.upn[i].lcn]:=up;
                                                end;
                                        end;
                                end;

                        end;

        end;
end;      }
procedure printContext(var v:ints);
var
i,j,jj:int64;
begin
    for i:=1 to v.nm do
    begin
        write('intent');
        write_menge(v.m[i]);
        writeln('extent');
        write_menge(v.ex[i]);
        writeln(v.lc[i].lcn);
        writeln('lcs');
        for jj:=1 to v.lc[i].lcn do
        begin
               { write_menge(v.lc[i].sett);         }
                write_menge(v.lc[i].lcm[jj]);
        end;
        writeln();
        writeln('Upns');
        for jj:=1 to v.upn[i].lcn do
                write_menge(v.upn[i].lcm[jj]);
        writeln('-------');

    end;
end;
end.
