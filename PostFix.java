import java.util.*;

class PostFix
{
    private static boolean DEBUG = false;
    private static Map<String, Integer> precMap = new HashMap<String, Integer>();
    private static void populatePrecedenceMap()
    {
        precMap.put("+", 1);
        precMap.put("-", 1);
        precMap.put("*", 2);
        precMap.put("/", 2);
        precMap.put("(", 3);
        precMap.put(")", 3);
    }
    private static boolean isVariable(String s)
    {
        return s.equalsIgnoreCase("x");
    }
    private static boolean isNum(String s)
    {
        return (!isVariable(s) && !isOperator(s));
    }
    private static boolean isOperator(String s)
    {
        return (s.equals("+") ||
                s.equals("-") ||
                s.equals("*") ||
                s.equals("/") ||
                s.equals("(") ||
                s.equals(")"));
    }
    private static boolean isParen(String s)
    {
        return (s.equals("(") || s.equals(")"));
    }
    private static boolean isOpeningParen(String s)
    {
        return (s.equals("("));
    }
    private static boolean isClosingParen(String s)
    {
        return (s.equals(")"));
    }
    private static ArrayList<String> convert(String exp)
    {
        ArrayList<String> lst = new ArrayList<>();
        Stack<String> opStack = new Stack<>();
        String p = "(?<=\\d)(?=\\D)|(?<=\\D)(?=\\d)|(?<=x)(?!x)|(?<!x)(?=x)|(?<=\\))|(?=\\()";
        String[] elements = exp.split(p);
        if(DEBUG) System.out.println(Arrays.toString(elements));
        String lastEle = "";
        boolean firstElement = true;
        for(String e:elements)
        {
            if(DEBUG) System.out.println(e);
            if(isOperator(e))
            {
                if(isOpeningParen(e) && !firstElement)
                {
                    // need to take care of missing * in exp "5(x+3)"
                    if(isClosingParen(lastEle) || isVariable(lastEle) || isNum(lastEle))
                    {
                        if(DEBUG) System.out.println("CHK1: lastEle:" + lastEle);
                        opStack.push("*");
                    }
                    opStack.push(e);
                }
                else if(isClosingParen(e))
                {
                    while(!isOpeningParen(opStack.peek()))
                    {
                        String op = opStack.pop();
                        if(!isParen(op))
                        {
                            lst.add(op);
                        }
                    }
                    if(isOpeningParen(opStack.peek()))
                    {
                        opStack.pop();
                    }
                }
                else
                {
                    if(DEBUG) System.out.println("stack empty?" + opStack.empty());
                    while(!opStack.empty())
                    {
                        String lastOp = opStack.peek();
                        if(DEBUG) System.out.println("lastOp:" + lastOp);
                        if(precMap.get(e) <= precMap.get(lastOp) &&
                           !isOpeningParen(lastOp))
                        {
                            lst.add(opStack.pop());
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(DEBUG) System.out.println("pushing in " + e);
                    opStack.push(e);
                }
            }
            else if(isVariable(e))
            {
                // need to take care of missing * in exp "(x-3)x"
                if(!firstElement)
                {
                    if(isClosingParen(lastEle) || isVariable(lastEle) || isNum(lastEle))
                    {
                        if(DEBUG) System.out.println("CHK2: lastEle:" + lastEle);
                        opStack.push("*");
                    }
                }
                lst.add("x");
            }
            else
            {
                // need to take care of missing * in exp "(x-3)5"
                if(isClosingParen(lastEle) || isVariable(lastEle))
                {
                    if(DEBUG) System.out.println("CHK3: lastEle:" + lastEle);
                    opStack.push("*");
                }
                lst.add(e);
            }
            lastEle= e;
            firstElement = false;
        }
        while(!opStack.empty())
        {
            lst.add(opStack.pop());
        }
        return lst;
    }
    public static int convertStringToInt(String s)
    {
        int n = 0;
        if(isVariable(s))
        {
            n = 7;
        }
        else
        {
            n = Integer.parseInt(s);
        }
        return n;
    }

    public static int apply(String op1, String op2, String op)
    {
        int n1 = convertStringToInt(op1);
        int n2 = convertStringToInt(op2);
        if(op.equals("+")) return n1 + n2;
        else if(op.equals("-")) return n1 - n2;
        else if(op.equals("*")) return n1 * n2;
        else if(op.equals("/")) return n1 / n2;
        else return 0;
    }
    public static int evaluatePostFixExp(ArrayList<String> pfExp)
    {
        Stack<String> calcStack = new Stack<>();
        for(String s:pfExp)
        {
            if(isOperator(s))
            {
                String op2 = calcStack.pop();
                String op1 = calcStack.pop();
                if(DEBUG) System.out.println(op1 + " " + s + " " + op2);
                int v = apply(op1, op2, s);
                calcStack.push(String.valueOf(v));
            }
            else
            {
                calcStack.push(s);
            }
        }
        String res = calcStack.pop();
        System.out.println("calcStack empty? " + calcStack.empty());
        return convertStringToInt(res);
    }

    public static void main(String[] args)
    {
        populatePrecedenceMap();
        String[] exps = new String[] {
            "72x-((289-33)/(32*2))*(6+19x)-8+x",
            "72x-(3+x)*(9-6)+5",
            "7x   *        (  3-x)",
            "(x+3)(7-3x)",
            "(  3-x)*5",
            "5x", "x", "5*2-3", "5-2*3"};

        for(String exp: exps)
        {
            String newExp = exp.replaceAll("\\s+", "");
            ArrayList<String> pfExp = convert(newExp);
            System.out.println("Original Expression: " + exp);
            System.out.println("PostFix Expression: " + pfExp);
            int res = evaluatePostFixExp(pfExp);
            System.out.println("expression evaluates to " + res);
            System.out.println("\n\n");
        }
    }
}
