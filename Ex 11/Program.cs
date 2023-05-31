using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;

namespace RegExpLab
{
    class Program
    {
        static void Main()
        {
            string orig = ReadXml();
            Console.WriteLine(orig.Length);
            Regex reAfterMainWord = new Regex(@"(<main-word>)\s*(</main-word>)([\s\-\(\).,\w\u0301\u2026\u2014˜]+)\s*(?=<)"); // исправляем случаи, когда слово спереди тега
            orig = reAfterMainWord.Replace(orig, "$1$3$2");
            Regex reBeforeMainWord = new Regex(@"(<bold>[\w\u0301\u2026-]+</bold>)\s*(<main-word>)\s*(</main-word>)"); // исправляем случаи, когда слово спереди тега
            orig = reBeforeMainWord.Replace(orig, "$2$1$3");
            Regex re = new Regex(@"<main-word>\s*</main-word>.{50}"); // ищем неверные теги(пустой main-word)
            MatchCollection mc = re.Matches(orig);
            foreach(var m in mc)
                Console.WriteLine(m);
            try{
                using (StreamWriter sw = new StreamWriter("new_dict.xml")){sw.Write(orig);}
            }
            catch (Exception ex){
                Console.WriteLine("Ошибка сохранения в файл: \"{0}\"\n{1}", "new_dict.xml", ex);
                return;
            }
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(orig);
        }
        static string ReadXml()
        {
            string orig;
            try{
                using (StreamReader sr = new StreamReader("Dictionary.xml")){orig = sr.ReadToEnd();}
            }
            catch (Exception ex){
                Console.WriteLine("Ошибка чтения файла: \"Dictionary.xml\"\n{0}", ex);
                throw ex;
            }
            return orig;
        }
    }
}
