Unit tricks;
Interface

procedure add_suffix(var fname : string; suffix : string);

Implementation
 
procedure add_suffix(var fname : string; suffix : string);
var ii	     : int64;

begin
   ii := 0;
   while (ii < length(fname)) and (fname[succ(ii)]<>'.') do ii := succ(ii);
   fname := Copy(fname,1,ii)+'.'+suffix;
end; { add_suffix }


end.		       








