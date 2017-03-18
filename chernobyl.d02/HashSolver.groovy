int ub(def b)
{
  return ((int)b)&0xff
}

int hash(def data)
{
  long res=0
  for (int i=0;i<data.size();i++)
  {
    int c=ub(data[i])
    // sxt c
    c=((c&0x80)==0x80)?(0xff00|c):c
    // c+=res
    c=(c+res)&0xffff
    // c*2^5-c
    res=((c<<5)-c)&0xffff
    //println("${i}:"+Long.toString(res,16)+":"+Integer.toString(c,16))
  }
  return res&0xffff
}

byte[] solve(byte[] data, int target)
{
  def full=data.toList().collect { it as int }
  while (full.size()<16)
    full+=48

  while((hash(full)&0x7)!=target)
  {
    full[-1]+=1
  }

  println("hash("+(full.collect { Integer.toString(ub(it),16) })+")="+Integer.toString(hash(full),16))

  return full.toList() as byte[]
}

byte[] data=args[0].decodeHex()
int target=Integer.parseInt(args[1],16)

res=solve(data,target)

println(res.encodeHex())
