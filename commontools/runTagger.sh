lifetime="ctauS1000"
ntags=1
name=$lifetime'_nt'$ntags
lifetime2='"'$lifetime'"'

c_al=(0.0 0.01 0.02 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2)
c_ip=(-1.0 -0.5 0.0 0.5 1.0 1.25 1.5 1.75 2.0 2.5 2.75)
c_ta=(-3.0 -2.5 -2.0 -2.25 -1.75 -1.5 -1.25 -1.0 -0.75 -0.5 0.0)
##if [$lifetime -eq ctauS1 && $ntags -eq 1]
##then
##c_al=(0.07 0.1 0.2)
##c_ip=(0.72 1.0 0.5)
##c_ta=(-2.04 -1.75 -2.25)
##elif [$lifetime == "ctauS1" && $ntags == 2]
##then
##c_al=(0.1 0.08 0.12)
##c_ip=(0.66 1.0 0.5)
##c_ta=(-2.16 -2.5 -2.0)
##elif [$lifetime == "ctauS10" && $ntags == 1]
##then
##c_al=(0.06 0.07 0.08)
##c_ip=(1.50 1.30 1.20)
##c_ta=(-1.5 -1.25 -1.75)
##elif [$lifetime == "ctauS10" && $ntags == 2]
##then
##c_al=(0.08 0.06 0.1)
##c_ip=(1.26 1.4 1.6)
##c_ta=(-1.5 -1.2 -1.4)
##elif [$lifetime == "ctauS100" && $ntags == 1]
##then
##c_al=(0.07 0.1 0.05)
##c_ip=(1.62 1.4 1.2)
##c_ta=(-1.38 -1.2 -1.5)
##elif [$lifetime == "ctauS100" && $ntags == 2]
##then
##c_al=(0.1 0.062 0.12)
##c_ip=(1.62 1.2 1.35)
##c_ta=(-1.5 -1.1 -1.2)
##elif [$lifetime == "ctauS1000" && $ntags == 1]
##then
##c_al=(0.06 0.1 0.15)
##c_ip=(1.68 1.15 1.8)
##c_ta=(-1.44 -1.85 -1.2)
##elif [$lifetime == "ctauS1000" && $ntags == 2]
##then
##c_al=(0.08 0.2 0.7)
##c_ip=(1.62 1.3 1.2)
##c_ta=(-1.08 -1.5 -1.25)
##else
##echo "error"
##exit
##fi


touch temp.txt
touch temp2.txt
touch temp4.txt
touch $name.txt
rm taggerTest/$name.txt
for i in {0..10}
do
   for j in {0..10}
   do
      for k in {0..10}
      do
         echo ${c_ip[i]} ${c_ta[j]} ${c_al[k]}>>temp2.txt
         root -l -b -q "tagger.C(${c_ip[i]},${c_ta[j]}, ${c_al[k]}, $ntags,  $lifetime2 )" >>temp.txt
      done
   done
done
awk '($1 !="Processing"){print}' temp.txt> temp3.txt
sed -i '/^$/d' temp3.txt
paste  temp2.txt temp3.txt >>temp4.txt
awk 'BEGIN {printf("%-9s %-9s %-9s %-13s %-13s %-15s  %-18s %-18s %-18s %-18s\n", \
                   "c_ip", "c_ta", "c_al", "Nsig", "Nbkg", "S/sqrt(S+B)", "S/sqrt(S+B+0.1B)", "S/sqrt(S+B+0.5B)", "S/sqrt(S+B+1.0B)", "S/sqrt(S+B+2.0B)")}
           {printf "%-9.2f %-9.2f %-9.2f %-13.6f %-13.6f", \
                    $1, $2, $3, $5, $7;
           if($5==0 && $7==0) printf "%-15.6f %-18.6f %-18.6f %-18.6f %-18.6f\n", 0, 0, 0, 0, 0; 
           else printf "%-15.6f %-18.6f %-18.6f %-18.6f %-18.6f\n", $5/sqrt($5 +$7), $5/sqrt($5 +$7 +0.1*$7), $5/sqrt($5 +$7 +0.5*$7), $5/sqrt($5 +$7 +1.0*$7), $5/sqrt($5 +$7 +2.0*$7) }' \
           temp4.txt >$name.txt

mv $name.txt taggerTest/
##(head -n 1 ctauS1_nt2.txt && tail -n +2 ctauS1_nt2.txt | sort -k6 -nr) > ctauS1_nt2_s.txt 
rm temp.txt
rm temp2.txt
rm temp3.txt
rm temp4.txt


##1 nt 1
##c_al=(0.05 0.1 0.15)
##c_ip=(0.84 1.2 0.7)
##c_ta=(-1.86 -2.0 -2.22)
##1 nt2
##c_al=(0.1 0.2 0.15)
##c_ip=(0.72 1.0 0.5)
##c_ta=(-2.22 -1.9 -1.65)

##10 nt 1
##c_al=(0.06 0.1 0.2)
##c_ip=(1.5 1.0 1.75)
##c_ta=(-1.5 -1.0 -2.0)
##10 nt 2
##c_al=(0.09 0.15 0.2)
##c_ip=(1.26 1.65 1.0)
##c_ta=(-1.5 -1.0 -1.8)

##100 nt 1
##c_al=(0.06 0.10 0.20)
##c_ip=(1.62 0.5 2.10)
##c_ta=(-1.44 -2.0 -0.75)
##100 nt 2
##c_al=(0.10 0.20 0.35)
##c_ip=(0.0 1.2 1.62)
##c_ta=(-1.2 -1.5 -2.0)

##1000 nt 1
##c_al=(0.12 0.7 0.2)
##c_ip=(1.68 1.4 1.2)
##c_ta=(-1.44 -1.6 -1.2)
##1000 nt2
##c_al=(0.12 0.7 0.2)
##c_ip=(1.44 1.25 -0.6)
##c_ta=(-2.76 -1.6 -2.2)
